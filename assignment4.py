# 4. Binary Search Tree -- CO1, CO2, CO3 
# Implement binary search tree and perform following operations: 
# a) Insert (Handle insertion of duplicate entry) 
# b) Delete 
# c) Search 
# d) Display tree (Traversal) 
# e) Display - Depth of tree 
# f) Display - Mirror image 
# g) Create a copy 
# h) Display all parent nodes with their child nodes 
# i) Display leaf nodes 
# j) Display tree level wise 
 
 
 
class Node: 
    def __init__(self, data): 
        self.data = data 
        self.left = None 
        self.right = None 
 
class BST: 
    def __init__(self): 
        self.root = None 
 
    # a) Insert (with handling duplicates) 
    def insert(self, root, data): 
        if root is None: 
            return Node(data) 
        elif data < root.data: 
            root.left = self.insert(root.left, data) 
        elif data > root.data: 
            root.right = self.insert(root.right, data) 
        else: 
            print(f"Duplicate entry '{data}' not allowed.") 
        return root 
 
    # b) Delete a node 
    def delete(self, root, key): 
        if root is None: 
            return root 
        if key < root.data: 
            root.left = self.delete(root.left, key) 
        elif key > root.data: 
            root.right = self.delete(root.right, key) 
        else: 
            # Node with one or no child 
            if root.left is None: 
                return root.right 
            elif root.right is None: 
                return root.left 
            # Node with two children 
            temp = self.find_min(root.right) 
            root.data = temp.data 
            root.right = self.delete(root.right, temp.data) 
        return root 
 
    def find_min(self, node): 
        while node.left is not None: 
            node = node.left 
        return node 
 
    # c) Search 
    def search(self, root, key): 
        if root is None or root.data == key: 
            return root 
        if key < root.data: 
            return self.search(root.left, key) 
        return self.search(root.right, key) 
 
    # d) Display tree (Traversal) 
    def inorder(self, root): 
        if root: 
            self.inorder(root.left) 
            print(root.data, end=' ') 
            self.inorder(root.right) 
 
    def preorder(self, root): 
        if root: 
            print(root.data, end=' ') 
            self.preorder(root.left) 
            self.preorder(root.right) 
 
    def postorder(self, root): 
        if root: 
            self.postorder(root.left) 
            self.postorder(root.right) 
            print(root.data, end=' ') 
 
    # e) Depth of tree 
    def depth(self, root): 
        if root is None: 
            return 0 
        left_depth = self.depth(root.left) 
        right_depth = self.depth(root.right) 
        return max(left_depth, right_depth) + 1 
 
    # f) Mirror image 
    def mirror(self, root): 
        if root: 
            root.left, root.right = self.mirror(root.right), self.mirror(root.left) 
        return root 
 
    # g) Create a copy 
    def copy(self, root): 
        if root is None: 
            return None 
        new_node = Node(root.data) 
        new_node.left = self.copy(root.left) 
        new_node.right = self.copy(root.right) 
        return new_node 
 
    # h) Display all parent nodes with their child nodes 
    def display_parents(self, root): 
        if root: 
            if root.left or root.right: 
                print(f"Parent: {root.data}", end=" => ") 
                if root.left: 
                    print(f"L: {root.left.data}", end=' ') 
                if root.right: 
                    print(f"R: {root.right.data}", end=' ') 
                print() 
            self.display_parents(root.left) 
            self.display_parents(root.right) 
 
    # i) Display leaf nodes 
    def display_leaves(self, root): 
        if root: 
            if root.left is None and root.right is None: 
                print(root.data, end=' ') 
            self.display_leaves(root.left) 
            self.display_leaves(root.right) 
 
    # j) Display tree level-wise (BFS) 
    def level_order(self, root): 
        if root is None: 
            return 
        queue = [root] 
        while queue: 
            current = queue.pop(0) 
            print(current.data, end=' ') 
            if current.left: 
                queue.append(current.left) 
            if current.right: 
                queue.append(current.right) 
 
# ---------- DEMO ---------- 
if __name__ == "__main__": 
    tree = BST() 
    root = None 
    elements = [50, 30, 70, 20, 40, 60, 80] 
 
    for el in elements: 
        root = tree.insert(root, el) 
 
    print("Inorder Traversal:") 
    tree.inorder(root) 
    print("\n\nDepth of tree:", tree.depth(root)) 
 
    print("\nLevel Order Traversal:") 
    tree.level_order(root) 
 
    print("\n\nMirror Image Inorder Traversal:") 
    mirrored = tree.mirror(tree.copy(root)) 
    tree.inorder(mirrored) 
 
    print("\n\nLeaf Nodes:") 
    tree.display_leaves(root) 
 
    print("\n\nParent Nodes with Children:") 
    tree.display_parents(root) 
 
    print("\n\nSearching for 40:", "Found" if tree.search(root, 40) else "Not Found") 
    print("Searching for 100:", "Found" if tree.search(root, 100) else "Not Found") 
 
print("\nDeleting 70...") 
root = tree.delete(root, 70) 
print("Inorder After Deletion:") 
tree.inorder(root) 