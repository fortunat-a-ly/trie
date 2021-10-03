#include <iostream>
#include <unordered_map>
#include <fstream>

struct Node {
    std::unordered_map<char, Node*> nextNodes;
    bool end;

    Node() {
        end = false;
    }
    Node(bool isLastChar) {
        end = isLastChar;
    }
    ~Node() {
        for (auto& kv : nextNodes) {
           delete kv.second;
        }
    }
};
struct Trie {
    Node* root = new Node(false);

    ~Trie() {
        delete root;
    }

    void insert(const std::string& word) {
        Node* start = root;
        for (const auto& s : word) {
            if (!start->nextNodes[s]) {
               start->nextNodes[s] = new Node;
            }
            start = start->nextNodes[s];
        }
        start->end = true;
    }
    void findByPrefix(const std::string& word) {
        Node* start = root;
        for (const auto& s : word) {
            start = start->nextNodes[s];
            
        }

        printWords(word, start);
    }
    void printWords(const std::string& word, Node* node) {
        if (node->end)
            std::cout << word << std::endl;

        for (const auto& ch : node->nextNodes) {
            std::string newWord = word;
            newWord.push_back(ch.first);
            printWords(newWord, node->nextNodes[ch.first]);   
        }
    }

};

void fill(Trie& tree) {
    std::ifstream file("words_alpha.txt");
    std::string word;
    while (file >> word) {
        tree.insert(word);
    }
}


int main()
{
    Trie tree;

    std::cout << "Enter: " << std::endl;
    std::string word;

    fill(tree);

    while (std::cin >> word) {
        tree.findByPrefix(word);
    }
}
      