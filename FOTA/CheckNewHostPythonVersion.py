import fnmatch
import subprocess
import time
import serial

from ftplib import FTP

ser = serial.Serial('/dev/ttyUSB0',9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE)

ftp = FTP('mohamedammar.mypressonline.com')

#if username and password is required.         
ftp.login('4434605_mohamedammar','MohamedAmmar2020')    

# if you have to change directory on FTP server. path file on server
ftp.cwd('/mohamedammar.mypressonline.com/')

# Get all files
files = ftp.nlst()

while True:

    # Download State file
    for file in files:
        if fnmatch.fnmatch(file, 'state.txt'):   #To download specific file.
            print("checking for update ...")

            try:
                ftp.retrbinary("RETR " + file ,open("/home/pi/codes/AutoHostPython/" + file, 'wb').write) #select path on pc/raspberry

            except EOFError:    # To avoid EOF errors.
                pass
                
    # Open the file in read mode
    with open('state.txt', 'r') as file:
        # Read the contents of the file
        data = file.read().strip()

    # Check if the data is equal to '1'
    if data == '1':
        print("State = 1, Update Exists!")
        
        # Get all files
        files = ftp.nlst()

        # Download files
        for file in files:
            if fnmatch.fnmatch(file, 'Application.bin'):   #To download specific files.
                print("Downloading..." + file)

                try:
                    ftp.retrbinary("RETR " + file ,open("/home/pi/codes/AutoHostPython/" + file, 'wb').write) #select path on pc/raspberry

                except EOFError:    # To avoid EOF errors.
                    pass
        
    
        #Target response variable
        msg = '0'
        msg1= 0
        
        
        
        #wait for target response
        print("waiting for target response")
        while msg != '7':
            
            # Notify target to send App file
            start_bootloader_msg='7'
            ser.write(start_bootloader_msg.encode())
            
            msg=ser.read()
            time.sleep(0.03)
            data_left = ser.inWaiting()
            msg += ser.read(data_left)
            #print(msg)
            msg1=msg.decode('ascii')
            
            #print(f"msg is {msg}")
            print(f"msg1 is {msg1}")
            
            #if target responded with 0x55
            if msg == b'\x07':
                print(" here b'\x07' ")
                print("sending Application.bin file")
                break
            else:
                print("invalid")
                
        #wait for target to reset to bootloader
        time.sleep(3)
    
        # Run Host Python script
        subprocess.run(["python", "/home/pi/codes/AutoHostPython/Host.py"])
        
        # Open the file in write mode to update its content
        with open('state.txt', 'w') as file:
            
            # Write '0' to the file
            file.write('0')
            print("State updated to 0")
        
        # Define the path to the modified state.txt file
        modified_file_path = "/home/pi/codes/AutoHostPython/state.txt"

        # Upload the modified file to the FTP server
        with open(modified_file_path, 'rb') as f:
            ftp.storbinary('STOR state.txt', f)
            
        # Print a message indicating successful upload
        print("Upload state.txt successful")
            

    elif data == '0':
        print("State = 0, No Update")
    else:
        print("Invalid state value")
        
    time.sleep(5)

    #ftp.close()
