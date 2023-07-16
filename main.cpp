#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Branch {
public:
    string elf_name;
    Branch *parent;
    vector<Branch *> children;

    explicit Branch(Branch *inParent) : parent(inParent) {}

    void setName(const string &inName) {
        if (inName != "None") {
            elf_name = inName;
        }
    }

    string getName() const {
        return elf_name;
    }

    int getChildrenCount() const {
        return children.size();
    }

    void treeGenerate(int begin, int finish) {
        srand(time(nullptr));

        int rand_branch = begin + (rand() % (finish - begin + 1));
        for (int i = 0; i < rand_branch; ++i) {
            auto *childBranch = new Branch(this);
            string name;
            cout << "Enter the name of the elf: ";
            getline(cin, name);
            childBranch->setName(name);
            cout << endl;
            children.push_back(childBranch);

        }
    }


    int getNeighbours() {
        int result = 0;

        if (parent->parent == nullptr) {
            for (auto &child: children) {
                if (!child->elf_name.empty()) {
                    ++result;
                }
            }
        } else if (parent->parent->parent == nullptr) {
            if (!parent->elf_name.empty()) {
                ++result;
            }
            for (auto &child: parent->children) {
                if (!child->elf_name.empty() and child->elf_name != elf_name) {
                    ++result;
                }
            }
        }

        return result;
    }

    Branch *findElf(const string &inName) {
        for (int i = 0; i < children.size(); ++i) {
            if (children[i]->getName() == inName) {
                return children[i];
            } else {
                for (int j = 0; j < children[i]->children.size(); ++j) {
                    if (children[i]->children[j]->getName() == inName) {
                        return children[i]->children[j];
                    }
                }
            }
        }
        return nullptr;
    }
};

int main() {

    vector<Branch *> trees(5);
    for (int i = 0; i < trees.size(); ++i) {
        trees[i] = new Branch(nullptr);
        trees[i]->treeGenerate(3, 5);

        for (int j = 0; j < trees[i]->getChildrenCount(); ++j) {
            trees[i]->children[j]->treeGenerate(2, 3);
        }
    }

    sleep(1);

    string find_elf;
    cout << "Input name: ";
    cin >> find_elf;

    cout << endl << endl << "\tAnswer!" << endl;
    Branch *current_elf = nullptr;
    for (auto &tree: trees) {
        current_elf = tree->findElf(find_elf);
    }

    if (current_elf == nullptr){
        cout << "The elf \"" << find_elf << "\" not found!" << endl;
    } else {
    cout << current_elf->getName() << " has " << current_elf->getNeighbours() << " neighbours.";
    }

    return 0;
}