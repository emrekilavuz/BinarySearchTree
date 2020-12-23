import time

## Recursive build function, it takes a number and places it in appropriate array location
## Parent at n, left child at 2n +1, and right child at 2n+2
def build_tree(bst_array, number, current_indeks):
    if(bst_array[current_indeks]==' '):
        bst_array[current_indeks] = number
        current_indeks = 0
    elif(number < bst_array[current_indeks]):
        build_tree(bst_array, number, 2*current_indeks + 1)
    elif(number > bst_array[current_indeks]):
        build_tree(bst_array, number, 2*current_indeks + 2)

## Recursive print function, prints tree as inorder traversal and writes to a file in append mode
def print_tree_inorder_recursive(sorted_file, bst_array, local_indeks):
    if(bst_array[local_indeks] == " "):
       return False
    print_tree_inorder_recursive(sorted_file, bst_array, 2*local_indeks + 1)
    print(bst_array[local_indeks])
    sorted_file.write(str(bst_array[local_indeks]) + " ")
    print_tree_inorder_recursive(sorted_file, bst_array, 2* local_indeks + 2)

number_list = []

## Read numbers through number_list array
number_file = open('numbers100.txt', mode = "r")
for line in number_file:
    splitted = line.split()
    for a_one in splitted:
        a_one = a_one.strip()
        number_list.append(int(a_one))

number_file.close()

bst_array = []

t_before = time.time()  ## Measure the start time

## Initialize the tree array, I don't know if there is a more efficient way
for i in range(50000):
    bst_array.append(" ")

## For every number in number_list place the number in appropriate index to bst_array
for i in range(len(number_list)):
    build_tree(bst_array, number_list[i], 0)

t_after = time.time()  ## Measure the end time

## Open the file in appending mode
sorted_number_file = open("sorted_100_py.txt" , mode = "a+")

## Print the tree and write to file in function
print_tree_inorder_recursive(sorted_number_file, bst_array, 0)

## Execution time
print(t_after-t_before)