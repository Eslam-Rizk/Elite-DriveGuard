import fnmatch
from ftplib import FTP

ftp = FTP('mohamedammar.mypressonline.com')

# Login to the FTP server
ftp.login('4434605_mohamedammar', 'MohamedAmmar2020')

# Change directory on the FTP server
ftp.cwd('/mohamedammar.mypressonline.com/')

# Define the path to the modified state.txt file
modified_file_path = "/home/pi/codes/AutoHostPython/state.txt"

# Upload the modified file to the FTP server
with open(modified_file_path, 'rb') as f:
    ftp.storbinary('STOR state.txt', f)

# Close the FTP connection
ftp.close()

# Print a message indicating successful upload
print("Upload state.txt successful")
