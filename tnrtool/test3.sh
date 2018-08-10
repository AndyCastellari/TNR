#/bin/bash
if [ -e temp3.bin ]
    then
        rm temp3.bin
    fi
if [ -e temp3.txt ]
    then
        rm temp3.txt
    fi
./tnrtool -t testObject3.json --if testObject3.bin --of temp3.txt --binary-text
./tnrtool -t testObject3.json --of temp3.bin --if temp3.txt
diff testObject3.bin temp3.bin
if [ $? -ne 0 ]
    then
    echo "FAILED"
    exit -1
    else
    echo "PASS"
    exit 0
    fi
