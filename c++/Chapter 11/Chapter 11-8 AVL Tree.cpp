struct Node{
	int val;
	int leftSize;
	int height;
	Node* left, *right;
	Node(int v) : val(v), leftSize(0), height(1), left(NULL), right(NULL){};
};
class AVLTree{
private:
	Node *root;
	Node* leftRotate(Node *root){
		Node* left = root, *right = root->right;
		root->right = right->left;
		right->left = root;
		right->leftSize += root ? root->leftSize + 1: 0;
		root = right;
		//update height
		root->height = max(height(root->left), height(root->right)) + 1;
		left->height = max(height(left->left), height(left->right)) + 1;
		return root;
	}
	Node* rightRotate(Node *root){
		Node* left = root->left, *right = root;
		root->left = left->right;
		root->leftSize = left->right ? left->right->leftSize + 1: 0;
		left->right = root;
		root = left;
		//update height
		root->height = max(height(root->left), height(root->right)) + 1;
		right->height = max(height(right->left), height(right->right)) + 1;
		return root;
	}
	int height(Node *root){
		return root ? root->height : 0;
	}
	int getBalance(Node *root){
		return root ? height(root->left) - height(root->right) : 0;
	}
	void inorder(Node * root){
		if(!root) return;
		inorder(root->left);
		cout<<"("<<root->val<<", "<<root->leftSize<<") ";
		inorder(root->right);
	}
	Node* insert(Node *root, int val){
		//insert node into BST
		if(!root) return new Node(val);
		if(val <= root->val){
			root->left = insert(root->left, val);
			root->leftSize++;
		}
		else if(root->val < val)
			root->right = insert(root->right, val);
		//update height
		root->height = max(height(root->left), height(root->right)) + 1;
		//get balance
		int balance= getBalance(root);
		//case 1: left-left
		if(balance > 1 && val < root->left->val)
			return rightRotate(root);
		//case 2: left-right
		else if(balance > 1 && val > root->left->val){
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		//case 3: right-right
		else if(balance < -1 && val > root->right->val)
			return leftRotate(root);
		//case 4: right-left
		else if(balance < -1 && val < root->right->val){
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}
	int getRankOfNumber(Node *root, int val){
		if(!root) return -1;
		if(root->val == val) 
			return root->leftSize;
		else if(val <= root->val)
			return getRankOfNumber(root->left, val);
		else{
			int right = getRankOfNumber(root->right, val);
			if(right == -1) return -1;
			else return right + (root->val < val ? 1 : 0) + root->leftSize;
		}
	
	}
public:
	AVLTree(){
		root = NULL;
	}
	void insert(int val){
		root = insert(root, val);
	}
	void inorder(){
		inorder(root);
		cout<<endl;
	}
	int getRankOfNumber(int val){
		return getRankOfNumber(root, val);
	}
};
int main(){
	int arr[] = {5, 1, 4, 4, 9, 7, 13, 3};
	vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
	AVLTree avltree;
	for(int i = 0; i < nums.size(); ++i){
		avltree.insert(nums[i]);
		avltree.inorder();
	}
	cout<<avltree.getRankOfNumber(4)<<endl;
	return 0;
}
