#include <bits/stdc++.h>

struct NOTEBOOK{
    std::string model;
    struct size{
        float x;
        float y;
        float z;
    } size;
    float mass;
    float price;
    float HDDmemoryGb;
};

struct NOTEBOOKNode{
    NOTEBOOK note;
    NOTEBOOKNode* next;
};

void AddNode(NOTEBOOKNode* head, const NOTEBOOK& note){
    NOTEBOOKNode* current = head;
    NOTEBOOKNode* prev = nullptr;
    while (current->note.model <= note.model && current != nullptr) {
        prev = current;
        current = current->next;
    }
    NOTEBOOKNode* newnode = new NOTEBOOKNode();
    newnode->note = note;
    newnode->next = current;
    if (prev != nullptr)
        prev->next = newnode;
}

int NumberOfNodes(NOTEBOOKNode* head){
    NOTEBOOKNode* current = head;
    int num = 0;
    while (current != nullptr){
        num++;
        current = current->next;
    }
    return num;
}

void AddToFile(const char* filename, NOTEBOOKNode* newnote){
    NOTEBOOKNode* current = newnote;
    std::fstream fin(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "File can't be opened. Check, whether file exists.\n";
        return;
    }
    std::streampos begin,end;
    begin = fin.tellg();
    fin.seekg (0, std::ios::end);
    end = fin.tellg();
    int num;
    if ((end - begin) == 0) num = 0;
    else {
        fin.seekg(0, std::ios::beg);
        fin.read(reinterpret_cast<char *>(&num), 4);
        fin.seekp(0, std::ios::beg);
    }
    num += NumberOfNodes(newnote);
    fin.write(reinterpret_cast<char *>(&num),4);
    fin.seekg(0, std::ios::end);

    while (current != nullptr) {
        fin.write(newnote->note.model.c_str(), sizeof(newnote->note.model));
        fin.write(reinterpret_cast<char *>(&newnote->note.size.x), sizeof(newnote->note.size.x));
        fin.write(reinterpret_cast<char *>(&newnote->note.size.y), sizeof(newnote->note.size.y));
        fin.write(reinterpret_cast<char *>(&newnote->note.size.z), sizeof(newnote->note.size.z));
        fin.write(reinterpret_cast<char *>(&newnote->note.mass), sizeof(newnote->note.mass));
        fin.write(reinterpret_cast<char *>(&newnote->note.price), sizeof(newnote->note.price));
        fin.write(reinterpret_cast<char *>(&newnote->note.HDDmemoryGb), sizeof(newnote->note.HDDmemoryGb));
        current = current->next;
    }
    fin.close();
}

void AddToFile(const char* filename, NOTEBOOK newnote){
    std::fstream fin(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "File can't be opened. Check, whether file exists.\n";
        return;
    }
    std::streampos begin,end;
    begin = fin.tellg();
    fin.seekg (0, std::ios::end);
    end = fin.tellg();
    int num;
    if ((end - begin) == 0) num = 0;
    else {
        fin.seekg(0, std::ios::beg);
        fin.read(reinterpret_cast<char *>(&num), 4);
        fin.seekp(0, std::ios::beg);
    }
    num++;
    fin.write(reinterpret_cast<char *>(&num),4);
    fin.seekg(0, std::ios::end);

    fin.write(newnote.model.c_str(), sizeof(newnote.model));
    fin.write(reinterpret_cast<char *>(&newnote.size.x), sizeof(newnote.size.x));
    fin.write(reinterpret_cast<char *>(&newnote.size.y), sizeof(newnote.size.y));
    fin.write(reinterpret_cast<char *>(&newnote.size.z), sizeof(newnote.size.z));
    fin.write(reinterpret_cast<char *>(&newnote.mass), sizeof(newnote.mass));
    fin.write(reinterpret_cast<char *>(&newnote.price), sizeof(newnote.price));
    fin.write(reinterpret_cast<char *>(&newnote.HDDmemoryGb), sizeof(newnote.HDDmemoryGb));
    fin.close();
}

void ReadFromFile(const char* filename, NOTEBOOKNode* list){
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()){
        std::cout << "Error, file couldn't be opened\n";
        return;
    }
    NOTEBOOKNode* note = new NOTEBOOKNode();
    list = note;
    int number;
    file >> number;
    for (auto i = 0; i < number; ++i){
        file >> note->note.model;
        file >> note->note.size.x;
        file >> note->note.size.y;
        file >> note->note.size.z;
        file >> note->note.mass;
        file >> note->note.price;
        file >> note->note.HDDmemoryGb;
        note->next = new NOTEBOOKNode();
        note = note->next;
    }
    note = nullptr;
    file.close();
}

void PrintList(NOTEBOOKNode*& list){
    NOTEBOOKNode* current = list;
    while (current != nullptr){
        std::cout << current->note.model << "\n";
        std::cout << current->note.size.x << "\n";
        std::cout << current->note.size.y << "\n";
        std::cout << current->note.size.z << "\n";
        std::cout << current->note.mass << "\n";
        std::cout << current->note.price << "\n";
        std::cout << current->note.HDDmemoryGb << "\n";
        current = current->next;
    }
}

void ChooseCurrent(char* filefromname, char* filetoname){
    std::ifstream filefrom(filefromname, std::ios::in | std::ios::binary);

    if (filefrom.bad()){
        std::cout<<"Check your input file.\n";
        return;
    }
    filefrom.seekg(0, std::ios::beg);

    int num;
    filefrom.read(reinterpret_cast<char *>(&num), 4);
    NOTEBOOKNode* list = new NOTEBOOKNode();
    list = nullptr;
    for (auto i = 0; i < num; ++i){
        filefrom.seekg(sizeof(NOTEBOOK) - sizeof(float), std::ios::cur);
        float memory;
        filefrom.read(reinterpret_cast<char *>(&memory), sizeof(float));
        if (memory < 1) {
            NOTEBOOK newnode;
            filefrom.seekg(sizeof(float) - sizeof(NOTEBOOK), std::ios::cur);
            filefrom.read(const_cast<char *>(newnode.model.c_str()), sizeof(newnode.model));
            filefrom.read(reinterpret_cast<char *>(&newnode.size.x), sizeof(newnode.size.x));
            filefrom.read(reinterpret_cast<char *>(&newnode.size.y), sizeof(newnode.size.y));
            filefrom.read(reinterpret_cast<char *>(&newnode.size.z), sizeof(newnode.size.z));
            filefrom.read(reinterpret_cast<char *>(&newnode.mass), sizeof(newnode.mass));
            filefrom.read(reinterpret_cast<char *>(&newnode.price), sizeof(newnode.price));
            filefrom.read(reinterpret_cast<char *>(&newnode.HDDmemoryGb), sizeof(newnode.HDDmemoryGb));
            AddNode(list, newnode);
        }
    };
    filefrom.close();
    AddToFile(filetoname, list);
}


int main() {
    NOTEBOOKNode* list = new NOTEBOOKNode();
    list = nullptr;
    char * notefile = const_cast<char *>("note.txt");
    char * binfile = const_cast<char *>("noteforbin.bin");
    ReadFromFile("note.txt", list);
    PrintList(list);
    NOTEBOOK newnote;
    newnote.model = "ABC";
    newnote.size.x = 15;
    newnote.size.y = 16;
    newnote.size.z = 17;
    newnote.HDDmemoryGb = 0.2;
    newnote.mass = 10;
    newnote.price = 100;
    AddToFile(notefile, newnote);
    ChooseCurrent(notefile, binfile);

    return 0;
}
