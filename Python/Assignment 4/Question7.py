class Tree(object):
    def __init__(self, value, nodes=None):
        self.value = value
        self.nodes = nodes

    def __repr__(self):
        if self.nodes:
            return 'Tree({0},{1})'.format(self.value, repr(self.nodes))
        return 'Tree({0})'.format(self.value)


def BuildTree(tree):
    """Build tree recursion"""
    if type(tree) != tuple:
        return Tree(tree)
    h = lambda x: 1 + max(list(map(h, x))) if type(x) == tuple else 0 #calc the hight of the node.
    return Tree(h(tree), list(map(BuildTree, tree))) #return Tree obj


def is_AVL_tree(tree):
    """check if the tree is AVL tree."""
    if tree is None:
        return True
    if isinstance(tree, list):
      lh = (lambda x: x.value if type(x) == Tree and x.nodes != None else 0)(tree[0])
      rh = (lambda x: x.value if type(x) == Tree and x.nodes != None else 0)(tree[1])
      if (abs(lh - rh) <= 1) and is_AVL_tree(tree[0]) is True and is_AVL_tree(tree[1]) is True:
          return True
    if type(tree) == Tree:
        if(is_AVL_tree(tree.nodes)):
            return True
    return False

# t1 = BuildTree((((1,2), 3), (4, (5, 6))))
# t2 = BuildTree(((2, 3), (4, (5, 6, (8, 2)))))
# t3 = BuildTree((((19, 1, 6), (1, (2, 3))), (((1, 2), 6), (5, 6, (8, 2)))))
#
# print(t1)
# print(t2)
# print(t3)
#
# print(is_AVL_tree(t1))
# print(is_AVL_tree(t2))
# print(is_AVL_tree(t3))

