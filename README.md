# CyclicList
## :clipboard:Description:clipboard:
Template implementation of a linear simply connected cyclic list.
## Auxiliary classes
* Iterator
* ConstIterator
### Purpose
Required for container iteration.
## :wrench:Methods:wrench:
* `front` (Returns the value of the first node)
* `back` (Returns the value of the last node)
* `size` (Returns the current number of nodes)
* `push_front` (Inserts a new item at the top of the list)
* `push_back` (Inserts a new item at the end of the list)
* `insert_before_if` (Inserts before, according to the specified condition)
* `insert_after_if` (Inserts after, according to the specified condition)
* `remove_nodes_if` (Removes all nodes that satisfy the condition)
* `erase` (Deletes a node at the specified position)
* `empty` (Checks for emptiness)
* `find` (Checks whether the node is contained in the list)
* `clear` (Сompletely clears the list)
### For iterators
* `begin` (Indicates the beginning of the list)
* `cbegin` (The same as `begin` only for ***constant*** nodes)
* `end` (Indicates the end of the list)
* `cend` (The same as `end` only for ***constant*** nodes)
## Link for cloning the repository:octocat:
`git clone https://github.com/Kuznetsov-Artyom/CyclicList.git`
