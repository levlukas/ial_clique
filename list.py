import os

def list_files(directory, indent=0):
    for item in os.listdir(directory):
        item_path = os.path.join(directory, item)

        if os.path.isdir(item_path):
            print(' ' * indent + '|____' + item)  
            list_files(item_path, indent + 6)  
        else:
            print(' ' * indent + '|______' + item)  

# Main execution
root_directory = '.'  
print(root_directory) 
list_files(root_directory)  
input()