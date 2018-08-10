#/bin/bash
if [ -e temp2.bin ]
    then
        rm temp2.bin
    fi
if [ -e temp2.txt ]
    then
        rm temp2.txt
    fi
./tnrtool -t testObject2.json --if testObject2.bin --of temp2.txt --binary-text
./tnrtool -t testObject2.json --of temp2.bin --if temp2.txt
diff testObject2.bin temp2.bin
if [ $? -ne 0 ]
    then
    echo "FAILED"
    exit -1
    else
    echo "PASS"
    exit 0
    fi
