import fnmatch
import subprocess

from ftplib import FTP

ftp = FTP('mohamedammar.mypressonline.com')

#if username and password is required.         
ftp.login('4434605_mohamedammar','MohamedAmmar2020')    

# if you have to change directory on FTP server. path file on server
ftp.cwd('/mohamedammar.mypressonline.com/')

# Get all files
files = ftp.nlst()

# Download State file
for file in files:
    if fnmatch.fnmatch(file, 'state.txt'):   #To download specific file.
        print("Downloading..." + file)

        try:
            ftp.retrbinary("RETR " + file ,open("D:\eslam\ITI\Embedded Linux\RaspberryPi\python\\" + file, 'wb').write) #select path on pc/raspberry

        except EOFError:    # To avoid EOF errors.
            pass
                
# Open the file in read mode
with open('state.txt', 'r') as file:
    # Read the contents of the file
    data = file.read().strip()

# Check if the data is equal to '1'
if data == '1':
    print("State is equal to 1")

elif data == '0':
    print("State is equal to 0")
else:
    print("Invalid state value")


#ftp.close()