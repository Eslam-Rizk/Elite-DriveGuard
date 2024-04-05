import fnmatch
from ftplib import FTP

ftp = FTP('mohamedammar.mypressonline.com')

#if username and password is required.         
ftp.login('4434605_mohamedammar','MohamedAmmar2020')    

# if you have to change directory on FTP server. path file on server
ftp.cwd('/mohamedammar.mypressonline.com/')

# Get all files
files = ftp.nlst()

# Download files
for file in files:
    if fnmatch.fnmatch(file, 'Application.bin'):   #To download specific files.
        print("Downloading..." + file)

        try:
            ftp.retrbinary("RETR " + file ,open("D:\eslam\ITI\Embedded Linux\RaspberryPi\python\\" + file, 'wb').write) #select path on pc/raspberry

        except EOFError:    # To avoid EOF errors.
            pass

ftp.close()