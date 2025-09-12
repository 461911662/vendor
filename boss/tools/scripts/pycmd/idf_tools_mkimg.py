#!/usr/bin/env python3
import struct
import sys
import os

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    import subprocess
    subprocess.check_call([sys.executable, '-m', 'pip', 'install', 'pyelftools~=0.31'])
    from elftools.elf.elffile import ELFFile

from .utils import fatal, info

# 打包头配置
MAGIC = b'BOSS'  # 4字节魔术字
HEADER_FORMAT = '<4sII'  # magic(4), entry(4), seg_count(4)
SEGMENT_FORMAT = '<III'  # vaddr(4), filesz(4), offset(4)

SPECIAL_ADDR_64KB = (0x3f400020, 0x400d0020)

def do_mkimage(elf_path, output_path):
    try:
        with open(elf_path, 'rb') as elf_file:
            elf = ELFFile(elf_file)

            # 1. 收集并验证PT_LOAD段
            load_segments = [seg for seg in elf.iter_segments() 
                           if seg['p_type'] == 'PT_LOAD']

            if not load_segments:
                raise ValueError("No loadable segments in ELF file")

            # 按虚拟地址排序确保正确的内存布局
            load_segments.sort(key=lambda x: x['p_vaddr'])

            # 计算有效段的数量
            load_segment_cnt = 0
            for seg in load_segments:
                if seg['p_filesz'] != 0:
                    load_segment_cnt += 1

            # 2. 准备打包头
            header = struct.pack(
                HEADER_FORMAT,
                MAGIC,
                elf.header['e_entry'],
                load_segment_cnt
            )

            # 计算头大小 (固定头 + 段信息表)
            header_size = len(header) + load_segment_cnt * struct.calcsize(SEGMENT_FORMAT)

            # 3. 构建段信息表和收集段数据
            seg_table = bytearray()
            seg_data = bytearray()
 
            current_offset = 0
            for seg in load_segments:
                # 验证段数据
                if seg['p_filesz'] == 0:
                    print(f"Warning: Empty segment at 0x{seg['p_vaddr']:08x}")
                    continue

                off = current_offset + header_size
                if seg['p_vaddr'] in SPECIAL_ADDR_64KB:
                    seg_data += b'\x00' * (0x10000 - (off % 0x10000))
                    current_offset += 0x10000 - (off % 0x10000)
                    off = current_offset + header_size

                # 添加段信息 (vaddr, filesz, offset)
                seg_table += struct.pack(SEGMENT_FORMAT,
                    seg['p_vaddr'],
                    seg['p_filesz'],
                    off
                )

                # 从获取的段中中，得到段的加载地址和存储地址
                print(f"seg['p_vaddr'] = {seg['p_vaddr']:08x} seg['p_offset'] = {off:08x} seg['p_filesz'] = {seg['p_filesz']}")

                # 处理段数据 (考虑可能的内存填充)
                data = seg.data()
                if len(data) < seg['p_filesz']:
                    # 填充零 (处理filesz > 实际数据的情况)
                    data += b'\x00' * (seg['p_filesz'] - len(data))
 
                lens = len(data)
                if lens % 4 != 0:
                    data += b'\x00' * (4 - lens % 4)
                seg_data += data
                current_offset += seg['p_filesz'] + (4 - lens % 4)

                filename = f"mkimg_{seg['p_vaddr']:08x}.bin"
                with open(filename, 'wb') as test:
                    test.write(data)


            # 4. 写入输出文件
            with open(output_path, 'wb') as out:
                out.write(header)
                out.write(seg_table)
                out.write(seg_data)

            # 打印摘要信息
            info(f"Packing summary for {os.path.basename(elf_path)}:")
            info(f"  Entry point: 0x{elf.header['e_entry']:08x}")
            info(f"  Load segments: {len(load_segments)}")
            info(f"  Header size: {header_size} bytes")
            info(f"  Total data size: {len(seg_data)} bytes")
            info(f"  Output file: {output_path}")

            return True
 
    except Exception as e:
        fatal(f"Error processing {elf_path}: {str(e)}", file=sys.stderr)
        return False

if __name__ == '__main__':
    if len(sys.argv) != 3:
        fatal(f"Usage: {sys.argv[0]} <input.elf> <output.bin>")
        sys.exit(1)
    
    success = do_mkimage(sys.argv[1], sys.argv[2])
    sys.exit(0 if success else 1)
