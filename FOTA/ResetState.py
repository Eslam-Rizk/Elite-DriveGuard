# Open the file in read mode
with open('state.txt', 'r') as file:
    # Read the contents of the file
    data = file.read().strip()

# Check if the data is equal to '1'
if data == '1':
    print("State is equal to 1")
    
    # Open the file in write mode to update its content
    with open('state.txt', 'w') as file:
        # Write '0' to the file
        file.write('0')
        print("State updated to 0")

elif data == '0':
    print("State is equal to 0")
else:
    print("Invalid state value")
