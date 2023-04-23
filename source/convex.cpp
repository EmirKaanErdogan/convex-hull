


/*

    BLG336E Analysis of Algorithms
    Assigment -2- 
    <Emir Kaan Erdoğan>
    <150200706>  

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <unordered_set>
#include <time.h>
#include <string.h>

using namespace std; 

class City{
    private:
        int id ;  
        int x ;
        int y ;
        int a ; // pount number
    public: 
        City();             // default constructor ;
        City(int,int,int,int);  // constructor with parameters; 
        City(City*) ;       // copy constructor 
        // getters
        int get_id()const {
            return this->id ;
        }
        int get_xPosition()const{
            return this->x;
        } 
        int get_yPosition()const {
            return this->y;
        }
        int get_aPosition()const{
            return this->a;
        }
        // setters 
        void set_id(int id){
            this->id= id; 
        }
        void set_xPosition(int x_position){
            this->x=x_position; 
        }
        void set_yPosition(int y_position){
            this->y=y_position;
        }
        void set_aPosition(int a){
            this->a=a; 
        }
        void print_object() const; 
};
// Default Constructor 
City::City(){
    cout<<"Welcome to Default Constructor ! "<<endl ; 
}
// Constructor with Parameters
City::City(int id,int x_positon,int y_position,int a){
    this->id = id ;
    this->x=x_positon;
    this->y=y_position;
    this->a=a; 
}
// Copy Constructor
City::City(City* copy_city){
    this->id = copy_city->id; 
    this->x=copy_city->x;
    this->y=copy_city->y;
    this->a=copy_city->a; 
}
// function to print the object
void City::print_object()const{
    cout<<"ID: "<<this->id<<", X pos: "<<this->x<<", Y pos: "<<this->y<<" , A pos: "<<this->a<<endl; 
}

// Function to create the vector of pointers to objects using the content vector
vector <City*> create_object(vector <vector<int> > &row){
    vector <City*> object_vector;
    for(int row_counter=0;row_counter<row.size();row_counter++){
        object_vector.push_back(new City(row_counter,row[row_counter][0],row[row_counter][1],row[row_counter][2]));
    }
    return object_vector; 
}

// function to find the cross-product 
double calculate_cross_product(const vector <City*>idx_city){
    // in the base case of the divider function, we have a city vector of size 3.
    // to arrange ccw order, first calculate the cross product of two vectors formed by this points.
    // the value of cp is the angle between vectors. if the value of cp>0 -> ccw 
    // else -> cw
    // Therefore, if the cp>0, we can return the points as they are, else we have to modify the vector. 
    
    // v1= (x2-x1 ; y2-y1) ; v2= (x3-x1; y3-y1); 
    double x1= double (idx_city[1]->get_xPosition())- double (idx_city[0]->get_xPosition()); 
    double y1= double (idx_city[1]->get_yPosition())- double (idx_city[0]->get_yPosition()); 
    double x2= double(idx_city[2]->get_xPosition())- double (idx_city[0]->get_xPosition()); 
    double y2= double (idx_city[2]->get_yPosition())- double (idx_city[0]->get_yPosition()) ;
    return ( (x1*y2) - (x2*y1));
}

// function to swap the elemenets of the vector of pointers to objects 
void swap_objects(vector <City*> &idx_city,int index_left, int index_right){
    City* temp= idx_city[index_left]; 
    idx_city[index_left]= idx_city[index_right] ; 
    idx_city[index_right]= temp; 
}

// function to provide counterclockwise array order 
vector <City*> ccw_arranger(vector<City*>& idx_city){
    // arrange ccw order by utilizing cross product
    // if cp>0 -> return else make modifications 
    if(idx_city.size()<=2){
        /*
        cout<<"Print ccw :"<<endl ; 
        for(int i=0 ;i<idx_city.size() ;i++){
            idx_city[i]->print_object(); 
        }
        */
        return idx_city; 
    }
    if (calculate_cross_product(idx_city)<0){
        // implement swap operation ! 
        swap_objects(idx_city,1,2); 
    }
    /*
    cout<<"Print ccw :"<<endl ; 
    for(int i=0;i<idx_city.size();i++){
        idx_city[i]->print_object(); 
    }
    */
    return idx_city; 
}
// function to creat the line using y=mx+b approach 
vector <double> create_line(const City p1 , const City p2 ){
    // y= mx+b ; 
    vector <double> line_coefficients(3) ; 
    double m = double( double (p2.get_yPosition()) - double (p1.get_yPosition()))/ double(double (p2.get_xPosition())-double (p1.get_xPosition())) ; 
    double b = double( (double (p2.get_yPosition()))- double (m *double (p2.get_xPosition()))); 
    //p1.print_object();
    //p2.print_object();
    line_coefficients[0]=(m); 
    line_coefficients[1]=(1.0);
    line_coefficients[2]=(b);
    // line vector contains the coefficients of x,y,b respectively.
    return line_coefficients; 
}
// function to clarify the position of the point wrt the line 
int get_position(const vector<double> line ,const vector <City*> city, int index){
    // line: ax-by+c=0 where a is the first index of the line vector, b is the second and c is the third
    double position=0; 
    position= line[0] * city[index]->get_xPosition()+ line[2] ;
    //position= position-city[index]->get_yPosition();
    // consider an arbitrary function that represents a line 
    // for instance for the graph 2x+1+y=0 
    // point (2,-1) is on the line
    // point (2,0) is above the line which can be visually confirmed, and by substituting the point into the equation
    // one can obtain ax+by+c >0 which is the met in the first if condition
    if(position<city[index]->get_yPosition()){ 
        
        return +1 ;  // below the line 
    }
    else if (position>city[index]->get_yPosition()){
        return -1 ; // above the line 
    }
    else {
    return 0 ; // position is initially 0, if it is on the line it satisfy the condition.  
    }
}

string detect_cases(vector <double> line ,vector <City*> idx_hull, int index){

    idx_hull[index%idx_hull.size()]->print_object();
    for(int i=0;i<idx_hull.size();i++){
        idx_hull[i]->print_object();
    }
    int position_next = get_position( line,idx_hull,( (index+1) %idx_hull.size() )) ;
    int position_prev = get_position(line,idx_hull,( (index-1+idx_hull.size()) %idx_hull.size() ) ); 
    if(position_next >=0 && (position_prev <=0) )
    {
        // next is above, prev is below, select next as pivot. 
        //cout<<"next"<<endl ;
        return "next"; 
    }
    else if ((position_next>=0) && (position_prev>=0) )
    {
        // both are above ; 
        //cout<<"Both are above "<<endl ; 
        return "lower_tangent"; 
    }
    else if ((position_next <=0 ) && (position_prev>=0))
    {
        // next is below, prev is above, select prev as pivot 
        //cout<<"Prev is above"<<endl ; 
        return "prev"; 
    }
    else if ((position_next <=0 ) &&(position_prev <=0) )
    {
        // both are below 
        return "upper_tangent"; 
    }
    return "EXIT_SUCCESS" ; 
}
// function to find the right most index of the vector 

int find_right_most_index(const vector <City*> idx_hull){
    int temp=0 ; 
    for(int i=1 ;i<idx_hull.size();i++){
        if(idx_hull[i]->get_xPosition()>idx_hull[temp]->get_xPosition()){
            temp= i ;
        }
    }
    return temp; 
}
// function to find the left most index of the vector
int find_left_most_index(const vector <City*> idx_hull){
    int temp=0 ; 
    for(int i=1;i<idx_hull.size();i++){
        if(idx_hull[i]->get_xPosition()<idx_hull[temp]->get_xPosition()){
            temp=i;
        }
    }
    return temp ; 
}

int updated_find_case(const City* p1, const City* p2 , const City* p3 ){
    double position= double ((p2->get_yPosition()-p1->get_yPosition())*(p3->get_xPosition()-p2->get_xPosition()))
    - double ((p3->get_yPosition()-p2->get_yPosition())* (p2->get_xPosition()-p1->get_xPosition())); 
    if(position == 0.0){
        return 0 ; 
    }
    else if(position<0.0){
        return -1; 
    }
    return +1 ;
}
// Merge function 
vector <City*> updated_combiner (vector <City*> &left_hull, vector<City*>right_hull){
    
    // first find right most point at the left hull
    // and left most point at the right hull 

    int left_tangent_index= find_right_most_index(left_hull);
    int right_tangent_index= find_left_most_index(right_hull); 
    int size_left= left_hull.size();
    int size_right= right_hull.size(); 
    vector <City*> combined_hull  ; 
    vector <double>upper_tangent_line ; 
    bool upper_tangent_found = false; 
    // cout<<"TRY TO FIND UPPER TANGENT ! "<<endl ; 

    while(!upper_tangent_found){
        upper_tangent_found= true; 
        upper_tangent_line=create_line(left_hull[left_tangent_index%left_hull.size()],right_hull[right_tangent_index%right_hull.size()]); 
        int position_next= get_position(upper_tangent_line,right_hull,(right_tangent_index+1+size_right)%size_right);
        int position_prev= get_position(upper_tangent_line,right_hull,(right_tangent_index+size_right-1)%size_right);
        while(! (position_next<=0 && position_prev<=0) ){
            //cout<<"UPPER TANGENT INFINITE LOOP POSSIBILITY 1"<<endl ; 
            right_tangent_index= (right_tangent_index -1+size_right) %right_tangent_index;
            upper_tangent_line=create_line(left_hull[left_tangent_index%size_left],right_hull[right_tangent_index%size_right]);    
            position_next= get_position(upper_tangent_line,right_hull,(right_tangent_index+1+size_right)%size_right);
            position_prev= get_position(upper_tangent_line,right_hull,(right_tangent_index+size_right-1)%size_right);
            //cout<<"POSITION NEXT: "<<position_next<<" POSITION PREV: "<<position_prev<<endl ; 
        }
        upper_tangent_line=create_line(left_hull[left_tangent_index%left_hull.size()],right_hull[right_tangent_index%right_hull.size()]);
        int position_left_hull_next = get_position(upper_tangent_line,left_hull,(left_tangent_index+1)%size_left);
        int position_left_hull_prev= get_position(upper_tangent_line,left_hull,(left_tangent_index+size_right-1)%size_left);
        while(!( position_left_hull_next<=0&&position_left_hull_prev<=0)){
            // cout<<"UPPER TANGENT INFINITE LOOP POSSIBILITY 2 "<<endl ; 
            left_tangent_index= (left_tangent_index+1 ) %size_left;
            upper_tangent_line=create_line(left_hull[left_tangent_index%left_hull.size()],right_hull[right_tangent_index%right_hull.size()]);
            position_left_hull_next = get_position(upper_tangent_line,left_hull,(left_tangent_index+1)%size_left);
            position_left_hull_prev= get_position(upper_tangent_line,left_hull,(left_tangent_index+size_right-1)%size_left);
            upper_tangent_found=false; 
        }
    }
    //cout<<"Upper tangent is founded !" <<endl ; 
    vector <int> upper_tangent_index(2); 
    upper_tangent_index[0]=left_tangent_index; 
    upper_tangent_index[1]= right_tangent_index ; 
    //cout<<"Print Upper Tangent Nodes"<<endl ; 
    /*
    left_hull[left_tangent_index%size_left]->print_object(); 
    right_hull[right_tangent_index%size_right]->print_object(); 
    */
    // having stored the nodes of the upper tangent, reset the indices.  
    left_tangent_index= find_right_most_index(left_hull);
    right_tangent_index= find_left_most_index(right_hull); 
    //cout<<"TRY TO FIND LOWER TANGENT "<<endl ; 
    vector <double> lower_tangent_vector ;
    bool lower_tangent_found= false; 
    while(!lower_tangent_found){
        lower_tangent_found=true ;
        lower_tangent_vector= create_line(left_hull[left_tangent_index%left_hull.size()],right_hull[right_tangent_index%right_hull.size()]); 
        int left_node_next= get_position(lower_tangent_vector,left_hull,(left_tangent_index+1)%size_left);
        int left_node_prev= get_position(lower_tangent_vector,left_hull,(left_tangent_index+size_left-1)%size_left);
        while(!(left_node_next>=0 && left_node_prev>=0)){
            //cout<<"LOWER TANGENT INFINITE LOOP POSSIBILITY 1 "<<endl ; 
            left_tangent_index= (left_tangent_index-1+size_left)%size_left;    
            lower_tangent_vector= create_line(left_hull[left_tangent_index%left_hull.size()],right_hull[right_tangent_index%right_hull.size()]); 
            left_node_next= get_position(lower_tangent_vector,left_hull,(left_tangent_index+1)%size_left);
            left_node_prev= get_position(lower_tangent_vector,left_hull,(left_tangent_index+size_left-1)%size_left);
        }
        lower_tangent_vector=create_line(left_hull[left_tangent_index%left_hull.size()],right_hull[right_tangent_index%right_hull.size()]);
        int position_right_hull_next= get_position(lower_tangent_vector,right_hull,(right_tangent_index+1)%size_right);
        int position_right_hull_prev= get_position(lower_tangent_vector,right_hull,(right_tangent_index-1+size_right)%size_right);
        while(!(position_right_hull_prev>=0 && position_right_hull_next>=0)){
            //cout<<"LOWER TANGENT INFINITE LOOP POSSIBILITY 2 "<<endl ; 
            right_tangent_index= (right_tangent_index+1)%size_right; 
            lower_tangent_vector=create_line(left_hull[left_tangent_index%left_hull.size()],right_hull[right_tangent_index%right_hull.size()]);
            position_right_hull_next=get_position(lower_tangent_vector,right_hull,(right_tangent_index+1)%size_right);
            position_right_hull_prev= get_position(lower_tangent_vector,right_hull,(right_tangent_index-1+size_right)%size_right);
            lower_tangent_found=false; 
        }
    }

    vector<int> lower_tangent_index(2);
    lower_tangent_index[0]= left_tangent_index; 
    lower_tangent_index[1]= right_tangent_index; 
    
    int index= upper_tangent_index[0]; 
    combined_hull.push_back(left_hull[index%size_left]); 
    while(index!=lower_tangent_index[0]){
        index= (index+1)%left_hull.size(); 
        combined_hull.push_back(left_hull[index]); 
    }
    index= lower_tangent_index[1];
    combined_hull.push_back(right_hull[index%right_hull.size()]);
    while(index!=upper_tangent_index[1]){
        index= (index+1)%right_hull.size(); 
        combined_hull.push_back(right_hull[index]); 
    } 
    /*
    cout<<"Print Combined Hull at the end :: : "<<endl ;
    for(int i=0;i<combined_hull.size();i++){
        combined_hull[i]->print_object(); 
    } 
    */
    return combined_hull ;
}   


vector<City*> seperater(vector <City*>&city_vector ) {
    // initialize the vector of pointer to objects for left and right halves;

    if (city_vector.size()<=3){
        return ccw_arranger(city_vector); 
    }
    int mid= city_vector.size()/2; 
    vector <City*> left; 
    vector <City*> right; 
    for(int i=0;i<mid;i++){
        left.push_back(city_vector[i]);
    }
    for(int i=mid;i<city_vector.size();i++){
        right.push_back(city_vector[i]); 
    }
    left = seperater(left); 
    right= seperater(right); 

    //return combiner(left,right); 
    return updated_combiner(left,right); 
} 

// Method to read the file, create the content vector and create the vector of objects to pointers using the content
vector<City*> read_file(string file_name,int* num_bakeryp,float* thresholdp,vector <int>&source_index_bakery_vector){
    vector <City*> city ;
    ifstream input_file (file_name);
    string line; 
    vector <vector <int> > row;
    if(!input_file.is_open()){
        cout<<"The file cannot be opened ! "<<endl;  
        return city; 
    }
    int row_counter=0  ;
    int no_city= 0 ;
    int no_bakery=0; 
    float threshold= 0 ;  
    while(getline(input_file,line)){
        stringstream ss(line);
        string column; 
        int col_counter=0; 
        while(getline(ss,column,' ')){
            if (row_counter==0){
                if (col_counter == 0) no_city = stoi(column); else if (col_counter == 1) no_bakery = stoi(column); 
                else if (col_counter == 2){
                    row.resize(no_city,vector<int>(3));                   
                    threshold = stof(column);
                }
                source_index_bakery_vector.resize(no_bakery); 
            }
            else if(row_counter==1){
                source_index_bakery_vector[col_counter]= stoi(column); 
            }
            else {
                    row[row_counter-2][col_counter]= stoi(column); 
            }
            col_counter+=1 ; 
        }
        row_counter+=1;
    }    
    *thresholdp= threshold ;
    return create_object(row); 
}
bool comparison(City * cityp1, City* cityp2) {
    return cityp1->get_xPosition()< cityp2->get_xPosition(); 
}
int detect_same_line(const City p1,const City p2 ,const City p3){
    vector <double> line = create_line(p1,p2); 
    double position_p3 = line[0]*p3.get_xPosition() + line[2]; 

    if(position_p3==p3.get_yPosition()){
        return 1; 
    }
    return 0 ; 
}

int write_output(string output, int size){
    ofstream outfile("convex.txt");
    if(!outfile.is_open()){
        cout<<"File cannot be opened !"<<endl ;
        return EXIT_FAILURE; 
    }
    outfile<<size;
    outfile<<endl ; 
    outfile<<output; 
    outfile.close();
    return EXIT_SUCCESS;
}
int main(int argc, char** argv){
    /*
        Keep your solution for Convex Hull Part in this file!
        Program Compile Command: g++ -std=c++11 -Wall -Werror conve.cpp -o convex
        Program Run Command: ./convex <input.txt>
        Expected input: /cases/case{$n}/input{$n}.txt
        Expected output: convex.txt
        Please, try to write clean and readable code. Remember to comment!!
    */
    string file_name=argv[1];
    int* num_cityp=new int[1]; 
    float* thresholdp= new float[1];
  
    vector <int> bakery_vector ;  
    vector <City*> city_vector= read_file(file_name,num_cityp,thresholdp,bakery_vector);
    // sort the vector by X using compare by x function, it returns true
    // if x of the first element is smaller than the second
    
    /*
    cout<<"CHECK WHETHER THE DATA IS EXTRACTDE PROPERLY! "<<endl ; 
    for(int i=0;i<city_vector.size();i++){
        city_vector[i]->print_object(); 
    }
    */ 
    sort(city_vector.begin(), city_vector.end(), comparison);
     
    vector<City*> vector = seperater(city_vector);
    int left_most_index= 0;
    int intersecting_points=0; 
    // find the leftmost index and begin the iteration there 
    for(int i=0 ;i<vector.size();i++){
        if(vector[left_most_index%vector.size()]->get_xPosition()>vector[i]->get_xPosition()){
            left_most_index=i ; 
        }
    }
    for(int i=left_most_index ;i<vector.size()+left_most_index;i++){

        if(detect_same_line(vector[i-1%vector.size()],vector[(i)%vector.size()],vector[(i+1)%vector.size()])==1)
        {
            intersecting_points++; 
            continue ; 
        }
    }
    cout<<vector.size()-intersecting_points<<endl ; 
    string output=""; 
    for(int i=left_most_index ;i<vector.size()+left_most_index;i++){

        if(detect_same_line(vector[i-1%vector.size()],vector[(i)%vector.size()],vector[(i+1)%vector.size()])==1)
        {
            continue ; 
        }
        output += to_string(vector[i%vector.size()]->get_id());
        output+="->";
        cout<<vector[i%vector.size()]->get_id()<<"->";
    }
    output+= to_string(vector[left_most_index]->get_id()); 

    cout<<vector[left_most_index]->get_id()<<endl; 
    cout<<"Print output: "<<endl ;
    cout<<output;
    write_output(output,vector.size()-intersecting_points);
    int no_city= *num_cityp; 
    float threshold= *thresholdp;  
    cout<<"No city: "<<no_city<<" ,Threshold: "<<threshold<<endl ; 
    delete [] num_cityp;
    num_cityp=nullptr; 
    delete [] thresholdp ; 
    thresholdp= nullptr;  
    exit(0);
}