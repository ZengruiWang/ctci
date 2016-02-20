#include <vector>
#include <iostream>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
void dfs(TreeNode* root, const int &target, vector<int> &path, vector<vector<int>> &res){
	if(!root) return;
	path.push_back(root->val);
	int sum = 0;
	for(int i = path.size() - 1; i >= 0; --i){
		sum += path[i];
		if(sum == target){
			res.push_back(vector<int>(path.begin() + i, path.end()));
		}
	}
	dfs(root->left, target, path, res);
	dfs(root->right, target, path, res);
	path.pop_back();
}
int main(){
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(1);
	root->left->right->left = new TreeNode(2);
	root->right = new TreeNode(1);
	root->right->left = new TreeNode(2);
	root->right->left->left = new TreeNode(4);
	vector<int> path;
	vector<vector<int>> res;
	dfs(root, 3, path, res);
	for(int i = 0; i < res.size(); ++i){
		for(int j = 0; j < res[i].size(); ++j){
			cout<< res[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
