//
// Created by msegura on 11/06/19.
//

#include "MetaController.h"

/**
 * Basic comparison structure used for building the Huffman tree
 */
struct comp{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};

MetaController::MetaController() {

    ifstream curr;
    curr.open("../metabase/current.json");
    string temp;
    while(getline(curr,temp)){
        cout<<"\nReading compressed current database: "+temp<<endl;
        currentDB.append(getUncompressed(temp));
    }
    curr.close();

    ifstream pre;
    pre.open("../metabase/previous.json");
    while(getline(pre,temp)){
        cout<<"\nReading compressed previous database: "+temp<<endl;
        previousDB.append(getUncompressed(temp));
    }
    pre.close();
}

void MetaController::commit(string database) {
    cout<<"\nProcessing new database commit...\n";
    previousDB=currentDB;
    currentDB=database;
    cout<<"New current database: "+currentDB<<endl;
    cout<<"New previous database: "+previousDB<<endl;
    writeJSONS();
}

string MetaController::rollBack() {
    cout<<"\nProcessing new database rollback, returning database to previous state...\n";
    string temp = previousDB;
    currentDB=previousDB;
    previousDB=temp;

    cout<<"\nNew current database: "+currentDB<<endl;
    cout<<"\nNew previous database: "+previousDB<<endl;

    writeJSONS();

    return currentDB;
}

void MetaController::writeJSONS() {
    cout<<"\nWriting database to JSON files...\n";
    ofstream currStream;
    currStream.open("../metabase/current.json", ofstream::trunc);
    currStream << getCompressed(currentDB);
    currStream.close();

    ofstream preStream;
    preStream.open("../metabase/previous.json", ofstream::trunc);
    preStream << getCompressed(previousDB);
    preStream.close();
    cout<<"\nWriting finished, JSON files up to date\n";
}

string MetaController::getCurrent() {
    return currentDB;
}

Node *MetaController::getNode(char ch, int freq, Node *left, Node *right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void MetaController::fillHuffmanCodes(Node *root, string str, GenericLinkedList<KeyValue> &map) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        string letter;
        letter.append(1,root->ch);
        KeyValue kv = KeyValue(letter,str);
        map.add(kv);
    }

    fillHuffmanCodes(root->left, str + "0", map);
    fillHuffmanCodes(root->right, str + "1", map);
}

string MetaController::getCompressed(string text) {
    cout<<"\n----------\nInitializing Huffman compression on string: "+text<<endl;

    unordered_map<char, int> freq;
    cout<<"\nCounting letters frequencies...\n";
    for (char ch: text)
        freq[ch]++;

    priority_queue<Node*, vector<Node*>, comp> pq;

    for (auto pair: freq){
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));

        string temp;
        char c = pair.first;
        temp.append(1,pair.first);
        cout <<"("+temp+" : "+to_string(pair.second)+") ";
    }
    cout<<endl;

    cout<<"\nCreating Huffman tree... (\'"<<'\u0000'<<"\' = no letter hold)\n";
    while (pq.size() != 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top();	pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));

        string temp = "(\'";
        temp.append(1,left->ch);
        temp.append("\':"+to_string(left->freq)+"-> "+to_string(sum)+" <-\'");
        temp.append(1,right->ch);
        temp.append("\':"+to_string(right->freq)+") ");
        cout<<temp;
    }
    cout<<"\nTree finished, root node has value "+to_string(pq.top()->freq)<<endl;

    Node* root = pq.top();

    GenericLinkedList<KeyValue> codes;

    cout<<"\nTraversing the tree in search of the letters' Huffman codes...\n";
    fillHuffmanCodes(root, "", codes);
    for(int i=0;i<*codes.getLength();i++){
        KeyValue kv = codes.get(i)->getData();
        cout << " ("+kv.getKey()<<":"<<kv.getValue()+") ";
    }
    cout<<endl;

    string compressed;
    for (char ch: text) {
        string chr;
        chr.append(1,ch);
        for(int i=0;i<*codes.getLength();i++){
            KeyValue kv = codes.get(i)->getData();
            if(chr==kv.getKey()){
                compressed+=kv.getValue();
            }
        }
    }

    cout << "\nCompressed database: " << compressed <<endl;

    string json = "{\"compressedDatabase\":\"";
    json.append(compressed+"\",\"codes\":[");
    for(int i=0;i<*codes.getLength();i++){
        KeyValue kv = codes.get(i)->getData();
        json.append("\""+kv.getKey()+"\":\""+kv.getValue()+"\"");
        if(i+1!=*codes.getLength())json.append(",");
    }
    json.append("]}");
    cout<<"Final JSON to be stored: "+json+"\nHuffman compression finished successfully\n----------\n";
    return json;
}

string MetaController::getUncompressed(string str) {
    cout<<"\n----------\nStarting Huffman uncompression of: "+str<<endl;
    str.erase(0,23);
    string db = str.substr(0, str.find("\""));
    str.erase(0, str.find("\"")+1);
    str.erase(0, str.find("[")+1);

    str.erase(str.size()-2,str.size());

    int n = std::count(str.begin(),str.end(),',')+1;

    cout<<"\nParsing and storing Huffman codes...\n";
    GenericLinkedList<KeyValue> codes;
    for(int i=0;i<n;i++){

        if(str.size()==0)break;

        if(str.at(0)==',')str.erase(0,1);

        char chr = str.at(1);
        string key = "";
        key.append(1,chr);

        str.erase(0,5);
        string value = str.substr(0, str.find("\""));
        str.erase(0, str.find("\"")+1);

        KeyValue kv = KeyValue(key,value);
        codes.add(kv);

        cout<<" (\'"+key+"\':"+value+") ";
    }cout<<endl;

    cout<<"\nBuilding the original text...\n";
    string original;
    string temp;
    int tempSize=1;
    bool exists;
    int index;
    while(!db.empty()){
        temp=db.substr(0,tempSize);
        exists=false;
        for(int i=0;i<*codes.getLength();i++) {
            KeyValue kv = codes.get(i)->getData();
            if(kv.getValue()==temp){
                exists=true;
                index=i;
            }
        }
        if(exists){
            KeyValue kv = codes.get(index)->getData();
            original.append(kv.getKey());
            db.erase(0,tempSize);
            tempSize=1;
            cout<<original<<endl;
        }else{
            tempSize++;
        }
    }
    cout<<"\nUncompression successfully finished\n----------\n";
    return original;
}
