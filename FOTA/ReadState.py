# Open the file in read mode
with open('state.txt', 'r') as file:
    # Read the contents of the file
    data = file.read().strip()

# Check if the data is equal to '1' or '0'
if data == '1':
    print("State is equal to 1")
elif data == '0':
    print("State is equal to 0")
else:
    print("Invalid state value")
