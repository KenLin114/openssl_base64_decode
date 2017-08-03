openssl base64 -d  -A -in 01_of_07_0_1048575 -out f.01 
openssl base64 -d -A -in 02_of_07_1048576_2097151 -out f.02
openssl base64 -d -A -in 03_of_07_2097152_3145727 -out f.03
openssl base64 -d -A -in 04_of_07_3145728_4194303 -out f.04
openssl base64 -d -A -in 05_of_07_4194304_5242879 -out f.05
openssl base64 -d -A -in 06_of_07_5242880_6291455 -out f.06
openssl base64 -d -A -in 07_of_07_6291456_7153699 -out f.07

cat f.* > fw.bin.fromBase64