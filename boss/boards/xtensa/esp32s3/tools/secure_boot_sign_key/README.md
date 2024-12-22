### bootloader record 
```bash
espsecure.py generate_signing_key --scheme ecdsa256 --version 2 bootloader_signing_key.pem
espsecure.py v4.8.dev4
ECDSA NIST256p private key in PEM format written to bootloader_signing_key.pem

md5sum bootloader_signing_key.pem
8cf90a26332cf343f3b50e3297a8a827  bootloader_signing_key.pem
```
