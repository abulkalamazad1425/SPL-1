#include <bits/stdc++.h>
#include <vector>
using namespace std;


#define MAX 30
#define COL 7
#define MAX_DATA 40

struct row_info
{
    int matchId;
    string attribute_Info[4];
    double numericAttribute_Info[7];
    string winner;

};

row_info values[MAX_DATA], all_values[MAX_DATA];

double Thresold;

struct node
{
    int attribute_number, child_number;
    string node_value ,node_name;
    double Thresold;
    double thresold[7];
    bool leaf = false;
    node **child;
    vector<row_info> row;
};


void calculate_gain_value(node *row_information);
void addChildren(node *children);
void mergeSort(std::vector<row_info> &arr,int sorting_colum_number, int left, int right);
void sortAttribute(node *r, int column);



void load_data()
{
    for (int i = 0; i < MAX_DATA; i++)
    {

        values[i].matchId = all_values[i].matchId ;
        for(int j=0;j<4;j++)
            values[i].attribute_Info[j] = all_values[i].attribute_Info[j];
        for(int j=4;j<7;j++){
            values[i].numericAttribute_Info[j] = all_values[i].numericAttribute_Info[j];
        }
        values[i].winner = all_values[i].winner;
    }
}

void load_all_data()
{
    char temp;
    int a, b, c;
    ifstream myFile("new.txt");
    for (int i = 0; i < MAX_DATA; i++)
    {   myFile >> all_values[i].matchId;
        for(int j=0;j<4;j++){
            myFile >> all_values[i].attribute_Info[j];
        }
        for(int j=4;j<7;j++)
            myFile >> all_values[i].numericAttribute_Info[j];
        myFile >> all_values[i].winner;
    }
}


struct node *create_tree()
{
    node *root = new node();
    root->leaf = false;
    for (int i = 0; i < MAX; i++)
    {
        root->row.push_back(values[i]);
    }
    root->node_name="ROOT";
    calculate_gain_value(root);
    root->child = new node *[root->child_number];

    node *children = new node();
    root->child[0] = children;
    if(root->attribute_number < 4){
        children->node_name = root->row[0].attribute_Info[root->attribute_number]; // Which catagory it divided
        int child_index = 0;
        string first_value = root->row[0].attribute_Info[root->attribute_number];
        for (int i = 0; i < root->row.size(); i++)
        {
            if (root->row[i].attribute_Info[root->attribute_number] == first_value)
            {
                children->row.push_back(root->row[i]);

            }
            else
            {

                addChildren(children);


                children = new node();

                children->node_name = root->row[i].attribute_Info[root->attribute_number];

                root->child[++child_index] = children;
                children->row.push_back(root->row[i]);
                first_value = root->row[i].attribute_Info[root->attribute_number];
            }
        }
    }
    else if(root->attribute_number >= 4){

        children->node_name = "numericAttribute"+ std::to_string(root->attribute_number) +"<=" + std::to_string(root->Thresold);
        int child_index = 0;
        bool flag = false;

        for (int i = 0; i < root->row.size(); i++)
        {
            if (root->row[i].numericAttribute_Info[root->attribute_number] <= root->Thresold || flag)
            {
                children->row.push_back(root->row[i]);

            }
            else
            {

                addChildren(children);

                children = new node();

                children->node_name = "numericAttribute"+ std::to_string(root->attribute_number) +">" + std::to_string(root->Thresold);

                root->child[++child_index] = children;
                children->row.push_back(root->row[i]);
                flag = true;
            }
        }

    }
    addChildren(children);
    cout <<"\t"<<root->node_name<<endl;

    for(int cld=0;cld<root->child_number;cld++){

        cout<< root->child[cld]->node_name<<" ";
        if(root->child[cld]->leaf)
            cout<< root->child[cld]->node_value;
        cout<<"     ";

    }
    cout<<endl<<endl;



    root->row.clear();
    return root;
}

bool checkSameWinner(node *children)
{
    set<string> temp;
    for (int i = 0; i < children->row.size(); i++)
    {
        temp.insert(children->row[i].winner);
    }

    if (temp.size() == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void addChildren(node *children)
{

    if (checkSameWinner(children)  )
    {
        children->leaf = true;

        children->node_value = children->row[0].winner;

        return;
    }

    children->leaf = false;
    calculate_gain_value(children);

    children->child = new node *[children->child_number];
    node *new_child = new node();

    if(children->attribute_number < 4){
        new_child->node_name = children->row[0].attribute_Info[children->attribute_number];

        children->child[0] = new_child;
        int child_index = 0;
        string first_value = children->row[0].attribute_Info[children->attribute_number];
        for (int i = 0; i < children->row.size(); i++)
        {
            if (children->row[i].attribute_Info[children->attribute_number] == first_value)
            {
                new_child->row.push_back(children->row[i]);
            }
            else
            {


                addChildren(new_child);

                new_child = new node();
                new_child->node_name = children->row[i].attribute_Info[children->attribute_number];

                children->child[++child_index] = new_child;

                new_child->row.push_back(children->row[i]);
                first_value = children->row[i].attribute_Info[children->attribute_number];
            }
        }
    }
    else if(children->attribute_number >= 4){
        if(children->Thresold ==0 ){
            if(rand()%2==0)
                children->node_value = "Pakistan";
            else
                children->node_value = "India";
            children->leaf=true;
            return;
        }

        new_child->node_name = "numericAttribute"+ std::to_string(children->attribute_number) +"<=" + std::to_string(children->Thresold);




        children->child[0] = new_child;

        int child_index = 0;
        bool flag = false;

        for (int i = 0; i < children->row.size(); i++)
        {
            if (children->row[i].numericAttribute_Info[children->attribute_number] <= children->Thresold || flag)
            {
                new_child->row.push_back(children->row[i]);
            }
            else
            {

                addChildren(new_child);


                new_child = new node();
                children->child[++child_index] = new_child;
                new_child->node_name = "numericAttribute"+ std::to_string(children->attribute_number) +">" + std::to_string(children->Thresold);




                new_child->row.push_back(children->row[i]);
                flag = true;
            }
        }

    }

    addChildren(new_child);
    cout <<"\t"<<children->node_name<<endl;

    for(int cld=0;cld<children->child_number;cld++){

        cout<< children->child[cld]->node_name<<" ";
        if(children->child[cld]->leaf)
            cout<< children->child[cld]->node_value;
        cout<<"     ";


    }
    cout<<endl<<endl;

    children->row.clear();

}


double find_attribute_probability(string num, int index, node *r)
{
    int result = 0;
    for (int i = 0; i < r->row.size(); i++)
    {
        if (r->row[i].attribute_Info[index] == num)
            result++;
    }
    return (double)result;
}

double find_class_probability(string class_value, node *r)
{
    int result = 0;
    for (int i = 0; i < r->row.size(); i++)
    {
        if (r->row[i].winner == class_value)
            result++;
    }
    return (double)result;
}


double find_probability_value(string num, string class_value, int index, node *r)
{
    int result = 0;
    for (int i = 0; i < r->row.size(); i++)
    {
        if (r->row[i].winner == class_value && r->row[i].attribute_Info[index] == num)
            result++;
    }

    return (double)result;
}


int sorting_colum_number;



void sortAttribute(node *r, int column)
{
    sorting_colum_number = column;
    mergeSort(r->row,sorting_colum_number,0,r->row.size()-1);
}

void mergeS(std::vector<row_info> &arr,int sorting_colum_number, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;



    std::vector<row_info> leftArr(arr.begin() + left, arr.begin() + left + n1);
    std::vector<row_info> rightArr(arr.begin() + middle + 1, arr.begin() + middle + 1 + n2);


    int i = 0, j = 0, k = left;


    while (i < n1 && j < n2) {
        if( sorting_colum_number >=4){
            if (leftArr[i].numericAttribute_Info[sorting_colum_number] <= rightArr[j].numericAttribute_Info[sorting_colum_number]) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }
        else{
            if (leftArr[i].attribute_Info[sorting_colum_number] <= rightArr[j].attribute_Info[sorting_colum_number]) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }

    }


    while (i < n1) {
        arr[k++] = leftArr[i++];
    }


    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}




void mergeSort(std::vector<row_info> &arr,int sorting_colum_number, int left, int right) {
    if (left < right) {
        int middle = (left + right)/2;
        mergeSort(arr,sorting_colum_number, left, middle);
        mergeSort(arr,sorting_colum_number, middle + 1, right);
        mergeS(arr,sorting_colum_number, left, middle, right);
    }
}




void calculate_gain_value(node *row_information)
{
    set<string> qualitativeAttribute_values;
    set<string> class_values;

    double total_row = (double)(row_information->row.size()), heighest_gain_value = 0, t1, t2, t3;
    double entropy = 0, row_entropy;

    for (int p = 0; p < row_information->row.size(); p++)
    {
        class_values.insert(row_information->row[p].winner);
    }

    for (auto &num2 : class_values)
    {
        t1 = find_class_probability(num2, row_information);
        t2 = (t1 / total_row) * (log2(t1 / total_row));
        entropy -= t2;
    }

    for (int i = 0; i < 7; i++)
    {

        if(i < 4){
            for (int p = 0; p < row_information->row.size(); p++)
            {
                qualitativeAttribute_values.insert(row_information->row[p].attribute_Info[i]);
            }
            row_entropy = 0;
            for (auto &num1 : qualitativeAttribute_values)
            {
                double t4 = 0;

                for (auto &num2 : class_values)
                {
                    t2 = find_attribute_probability(num1, i, row_information);
                    t1 = (find_probability_value(num1, num2, i, row_information) / t2);
                    if (t1 == 0)
                        continue;
                    t3 = log2(t1);
                    t4 -= (t1 * t3);
                }
                t2 = (t2 / total_row);
                row_entropy += (t2 * t4);
            }
        }

        else if(i >= 4){
                sortAttribute(row_information, i);

            

            double lowestEntropy = 5;
             row_entropy = 0;
            for(int q=0;q< row_information->row.size();q++){



                    double t4 = 0;

                        t2 = q+1;

                        t1=0;
                        int s;
                        for( s=0;s<t2;s++){
                            if (row_information->row[s].winner == "India" ){
                                t1++;
                            }
                        }

                        if(t1==0 || t1==t2)
                            continue;
                        t3 = - ((t1/t2) * log2(t1/t2) + ((t2-t1)/t2)*log2((t2-t1)/t2));
                        t3 = ((q+1)/total_row)*t3;
                        t1=0;
                        t2= row_information->row.size() - t2;
                        for(  ;s<row_information->row.size();s++){
                            if (row_information->row[s].winner == "India" ){
                                t1++;
                            }
                        }
                        if(t1==0 || t1==t2)
                            continue;
                        t4 = - ((t1/t2) * log2(t1/t2) + ((t2-t1)/t2)*log2(((t2-t1)/t2)));
                        t4 = (t2/total_row)*t4;
                        double t5 = t3 + t4;
                        if(t5 < lowestEntropy ){
                            lowestEntropy=t5;

                            row_information->thresold[i] = row_information->row[q].numericAttribute_Info[i];
                            row_entropy = t5;
                        }



            }

        }

        if ((entropy - row_entropy) > heighest_gain_value && i<4)
        {
            heighest_gain_value = (entropy - row_entropy);
            row_information->attribute_number = i;
            row_information->child_number = qualitativeAttribute_values.size();
        }
        else if((entropy - row_entropy) > heighest_gain_value){
            heighest_gain_value = (entropy - row_entropy);
            row_information->attribute_number = i;
            row_information->child_number = 2;
            row_information->Thresold = row_information->thresold[i];
        }

        qualitativeAttribute_values.clear();
    }
    sortAttribute(row_information, row_information->attribute_number);
    
}


string find_decision(node *level_data, row_info test_data)
{


    string ch;
    int i = 0;
    if (level_data->leaf )
    {


            ch = level_data->node_value;


    }
    else
    {

        if(level_data->attribute_number < 4){

            for (i = 0; i < level_data->child_number; i++)
            {

                if (level_data->child[i]->node_name == test_data.attribute_Info[level_data->attribute_number])
                {
                    ch = find_decision(level_data->child[i], test_data);
                    break;
                }


            }
            if (i == level_data->child_number)
                ch = find_decision(level_data->child[i - 1], test_data);
        }
        else{


                if((test_data.numericAttribute_Info[level_data->attribute_number] <= level_data->Thresold) ){
                    string childName = "numericAttribute"+ std::to_string(level_data->attribute_number) +"<=" + std::to_string(level_data->Thresold);
                    if(level_data->child[0]->node_name == childName){

                        ch = find_decision(level_data->child[0], test_data);

                    }
                    else{
                       ch = find_decision(level_data->child[1], test_data);
                    }

                }
                else{
                    string childName = "numericAttribute"+ std::to_string(level_data->attribute_number) +">" + std::to_string(level_data->Thresold);
                    if(level_data->child[0]->node_name == childName){
                        ch = find_decision(level_data->child[0], test_data);

                    }
                    else{
                       ch = find_decision(level_data->child[1], test_data);
                    }
                }

            }
    }

    return ch;
}

bool testing(node *root, row_info test_data)
{
    string ch = find_decision(root, test_data);

    if (ch == test_data.winner)
    {
        
        return true;
    }
    else
    {
        return false;
    }
}

int Prediction()
{
    node *roots;
    load_all_data();

    load_data();

    roots = create_tree();


    int match = 0, disMatch = 0;

    for (int i = 30; i < MAX_DATA; i++)
    {

        if (testing(roots, values[i]))
            match++;
        else
            disMatch++;
    }

    cout << match << " " << disMatch << endl;
    double Accuracy = (double)(match ) / (double)(match + disMatch);
    cout << "Accuracy is: " << Accuracy * 100 << endl<<endl;
    row_info Current_match;
    int option;

    cout << "To predict a match enter  all attribute value in the formate:"<<endl;
    cout <<"TossWinner , TossDecission , City , Stadium , 1stInningsTotalRun , 1stInningsTotalWicket , RequiredRunRate  "<<endl;
    while(1){
        int i=0;
        cout <<"Do you want to predict one: (press (1)) ";
        cin >> option;
        if(option != 1)
            break;
        for( i=0;i<4;i++)
            cin >> Current_match.attribute_Info[i];
        while(i<7){
            cin >> Current_match.numericAttribute_Info[i];
            i++;
        }
        string ch = find_decision(roots, Current_match);
        cout <<"\n\n\n"<<"Predicted Team:  "<<ch<<"\n\n\n" <<endl;
    }

    return 0;
}
