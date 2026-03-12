///     Name                 ID       Group
///   Abdelrahman Ahmed    20160127     5
///   Shiref Tarek         20160115     5



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const char* fileName="Data.txt";

short stringToInt(string );
void searchInFile(string );
int searchInData(string ,string );
void addRecord();
string getAllTheData();
void saveAllTheDataAgain(string );
void deleteRecord(string );
string getId();
void  visualizeFile();
void updateRecord(string id);
void compactFile() ;


class NoteBook
{
public:
    string id;
    string brand;
    string desc;
    string os;
    NoteBook();
    void addThisRecord();
    void justify();
    friend istream& operator>>(istream &,NoteBook &);
    string makeBuffer();

};

int main()
{
    while(true)
    {
        cout<<"Choose what you want to do (by its number) :"
            <<"\n\t1-add a new record"
            <<"\n\t2-search for a record by id"
            <<"\n\t3-delete a record by id"
            <<"\n\t4-update a record by id"
            <<"\n\t5-Visualize File"
            <<"\n\t6-Compact the file"
            <<"\n\t7-Stop the program\n";
        int c;
        cin>>c;
        if(c==7)
            break;
        else if(c==1)
            addRecord();
        else if(c==2)
        {
            string id=getId();
            searchInFile(id);
        }
        else if(c==3)
        {
            string id = getId();
            deleteRecord(id);
        }
        else if(c==4)
        {
            string id = getId();
            updateRecord(id);
        }
        else if(c==5)
        {
            visualizeFile();
        }
        else if(c==6)
        {
            cout<<endl<<"---> Done  ;)"<<endl;
            compactFile();
        }

    }

    return 0;
}


/*** Start Class Methods ***/
NoteBook::NoteBook()
{
    id="";
    brand="";
    desc="";
    os="";
}

string NoteBook::makeBuffer()
{
    string buffer;
    buffer=id;
    buffer+='|';
    buffer+=brand;
    buffer+='|';
    buffer+=desc;
    buffer+='|';
    buffer+=os;
    buffer+='|';
    return buffer;
}
/// To add an object to the file
void NoteBook::addThisRecord()
{
    ofstream stream(fileName,ios::app);
    string buffer = makeBuffer();
    short len=buffer.length();
    if(len<10)
        stream<<'0';
    stream<<len<<buffer;
    stream.close();

}


/// Justify Functions to make the limits
void NoteBook::justify()
{
    id=id.substr(0,20);
    brand=brand.substr(0,20);
    desc=desc.substr(0,50);
    os=os.substr(0,20);
}

/*** End Class Methods ***/


/** Start I/P Operator overloading for NoteBook **/

istream& operator>>(istream &in,NoteBook &note)
{
    cout<<"\nPlease enter note book Data : \n\tID (Max : 20)>>";
    getline(in,note.id);
    while(note.id=="")
        getline(in,note.id);
    cout<<"\tBrand (Max : 20)>>";
    getline(in,note.brand);
    while(note.brand=="")
        getline(in,note.brand);
    cout<<"\tProcessor desc.(Max : 50)>>";
    getline(in,note.desc);
    while(note.desc=="")
        getline(in,note.desc);
    cout<<"\tOperating System(Max : 20)>>";
    getline(in,note.os);
    while(note.os=="")
        getline(in,note.os);
    note.justify();
}

/** End I/P Operator overloading for NoteBook **/

/** Start Update Record **/

void updateRecord(string id)
{
    string data = getAllTheData();
    int ind=searchInData(id,data);
    if(ind == -1)
        cout<<"Not Found \n"<<endl;
    else
    {

        cout<<"We have found it and now we are waiting for your updates \n\n";
        NoteBook note;
        cin>>note;
        note.justify();
        string buffer = note.makeBuffer();
        int noteLen=buffer.length();
        string temp=data.substr(ind,2);
        int recordLen=stringToInt(temp);
        if(noteLen != recordLen)
        {
            data[ind+2]='*';
            saveAllTheDataAgain(data);
            note.addThisRecord();

        }
        else
        {
            for(int i=0;i<noteLen;i++)
            {
                data[ind+2+i]=buffer[i];
            }
            saveAllTheDataAgain(data);
        }
        cout<<"Data has updated successfully \n"<<endl;

    }
}

/** End Update Record **/


/** Start Add Record Function **/
void addRecord()
{
    NoteBook note;
    cin>>note;
    note.addThisRecord();
}
/** Start Add Record Function **/

/** Start Searching Functions **/

void searchInFile(string id)
{
    string data=getAllTheData();
    int ind=searchInData(id,data);
    if(ind == -1)
        cout<<"Not found \n"<<endl;
    else
    {
        cout<<"We found the notebook and here is its data :\n\n";
        string temp=data.substr(ind,2);
        int len=stringToInt(temp);
        temp="";
        for(int i=ind+2;i<ind+2+len;i++)
        {

            if(data[i]=='|')
            {
                cout<<temp<<"\t";
                temp="";
            }
            else
            {
                temp+=data[i];
            }

        }

    }

}
int searchInData(string key,string data)
{

    for(int i=0;i<data.length();i++)
    {
        string temp=data.substr(i,2);
        int len=stringToInt(temp);
        temp="";
        int j=2+i;
        while(data[j]!='|')
        {
            temp+=data[j++];
        }
        if(temp==key)
        {
            return i;
        }
        i+=len+1;


    }

    return -1;
}


/** End Searching Functions **/


/** Start Deleting Function **/

void deleteRecord(string id)
{
    string data=getAllTheData();
    int ind=searchInData(id,data);
    if(ind == -1)
        cout<<"Not found \n"<<endl;
    else
    {
        data[ind+2]='*';
        cout<<"Record has been deleted successfully \n"<<endl;
    }
    saveAllTheDataAgain(data);
}
/** End Deleting Function **/


/** Start Visualize File **/
void  visualizeFile()
{
    string data = getAllTheData();
    for(int i=0;i<data.length();i++)
    {
        string temp=data.substr(i,2);
        int len=stringToInt(temp);
        int j=2+i;
        if(data[2+i]=='*')
            cout<<"*";
        else
            cout<<"-";
        i+=len+1;
    }
    cout<<endl;
}
/** End Visualize File **/


/// Function to get all the data as a string
string getAllTheData()
{
    ifstream stream(fileName,ios::in);

    // Read all the data
    string data((std::istreambuf_iterator<char>(stream)),
                 std::istreambuf_iterator<char>());
    stream.close();
    return data;
}
void saveAllTheDataAgain(string data)
{
    ofstream stream(fileName,ios::out|ios::trunc);
    stream<<data;
}
short stringToInt(string str)
{
    short x;
    stringstream stream;
    stream<<str;
    stream>>x;
    return x;
}

string getId()
{
    string iD;
    cout<<"Please Enter the ID >> ";cin>>iD;
    return iD;
}
void compactFile()
{
    string data = getAllTheData();
    int i=0;
    while(i<data.length())
    {
        string temp=data.substr(i,10); /******************/
        temp=data.substr(i,2);
        int len=stringToInt(temp);
        if(data[i+2]=='*')
        {
            string subData="";
            data = data.substr(0,i) +  data.substr(i+len+2,data.length()- (i+len+1)) ;
            i-=1;
        }
        i++;
    }
    saveAllTheDataAgain(data);
}
