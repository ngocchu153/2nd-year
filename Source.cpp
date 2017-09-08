#include <iostream>
 
using namespace std;

template <class heso,class somu>
class DonThuc{
public:
    heso heSo;
    somu soMu;
    DonThuc* next;
};
template <class heso,class somu>
class DaThuc{
private:
    DonThuc<heso,somu>* head;
public:
    DaThuc() {head=NULL;}
    bool IsEmpty() { return head == NULL; }
    void ThemDonThuc(heso heSo,somu soMu);
    void chenDonThuc(heso heSo,somu soMu);
    void xoaDonThuc(somu soMu);
    DaThuc operator+(const DaThuc);
    DaThuc operator*(const DaThuc);
    void display();
};

template <class heso,class somu>
void DaThuc<heso,somu>::chenDonThuc(heso heSo,somu soMu) {
    DonThuc<heso,somu> *newDT = new DonThuc<heso,somu> ;
    newDT->heSo = heSo;
    newDT->soMu = soMu;
    newDT->next = NULL;
    if (head == NULL)
        head = newDT;
    else {
        if(head->soMu < newDT->soMu) {                                      //insert head
            newDT->next = head;
            head = newDT;
            return;
        }
        DonThuc<heso,somu> *prev = new DonThuc<heso,somu>;                  //insert middle
        for(DonThuc<heso,somu>  *curr = head; curr ; curr=curr->next) {
            if(curr->soMu==newDT->soMu) {                                   //update heSo
                curr->heSo+=newDT->heSo;
                return;
            }
            if (curr->soMu<newDT->soMu) {
                prev->next = newDT;
                newDT->next = curr;
                return;
            }
            prev=curr;
        }
        DonThuc<heso,somu> * curr = head;                                   //insert last
        while(curr->next)
            curr=curr->next;
        curr->next = newDT;
        return;
    }
    return;
}

template <class heso,class somu>
void DaThuc<heso,somu>::xoaDonThuc(somu soMu) {
    if (head->soMu == soMu) {
        DonThuc<heso, somu>* temp = head;
        head = head->next;
        delete temp;
    }
    else {
        DonThuc<heso,somu>  *curr;
        DonThuc<heso,somu> *prev = new DonThuc<heso,somu>;
        for(curr = head; curr->next ; curr=curr->next) {
            if (curr->soMu==soMu) {
                prev->next = curr->next;
                curr->next = NULL;
                delete curr;
                break;
            }
            prev=curr;
        }
        delete prev->next;
        return;
    }
    return;
}

template <class heso,class somu>
void DaThuc<heso,somu>::display() {
    if(!head) {
        cout << "0" << endl;
        return;
    }
    DonThuc<heso,somu>* curr = head;
    for (;curr;curr = curr->next) {
        if (curr->heSo==0) {
            xoaDonThuc(curr->soMu);
            continue;
        }
        if (curr->heSo > 0 && curr!=head) cout<< "+";
        if (curr->soMu==0) {
            cout << curr->heSo;
            break;
        }
        cout << curr->heSo << "x^" << curr->soMu;
    }
    cout << endl;
    delete curr;
    return;
}

template <class heso,class somu>
DaThuc<heso,somu> DaThuc<heso,somu>::operator+(const DaThuc P) {
    DaThuc<heso,somu> result;
    DonThuc<heso,somu>* curr = head;
    for(;curr;curr=curr->next) {
        result.chenDonThuc(curr->heSo, curr->soMu);
    }
    curr=P.head;
    for(;curr;curr=curr->next) {
        result.chenDonThuc(curr->heSo, curr->soMu);
    }
    delete curr;
    return result;
}

template <class heso,class somu>
DaThuc<heso,somu> DaThuc<heso,somu>::operator*(const DaThuc P) {
    DaThuc result;
    for(DonThuc<heso,somu>* curr=head;curr;curr=curr->next) {
        for(DonThuc<heso,somu>* currP=P.head;currP;currP=currP->next) {
            result.chenDonThuc(curr->heSo*currP->heSo, curr->soMu+currP->soMu);
        }
    }
    return result;
}



int main() {
    DaThuc<float,int> P,P1,R1,R2;
    P.chenDonThuc(10,3000);
    P.chenDonThuc(4,2);
    P.chenDonThuc(7,0);
    
    P1.chenDonThuc(-2,0);
    
    
    R1=P+P1;
    R2=P*P1;
    P1.display();
    R1.display();
    R2.display();
    return 0;
}
