

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
void swap_objects(vector <City*> &idx_city,int index_left, int index_right){
    City* temp= idx_city[index_left]; 
    idx_city[index_left]= idx_city[index_right] ; 
    idx_city[index_right]= temp; 
}
vector <City*> ccw_arranger(vector<City*>& idx_city){
    cout<<"Welcome to ccw arranger ! "<<endl ; 
    // arrange ccw order by utilizing cross product
    // if cp>0 -> return else make modifications 
    if (calculate_cross_product(idx_city)<0){
        // implement swap operation ! 
        swap_objects(idx_city,1,2); 
    }
    cout<<"Print Arranged vector !" <<endl ; 
    for(int i=0;i<idx_city.size();i++){
        idx_city[i]->print_object();
    }
    return idx_city; 
}
// function to clarify the position of the point wrt the line 
vector <double> create_line(const City p1 , const City p2 ){
    // y= mx+b ; 
    vector <double> line_coefficients(3) ; 
    double m = double(p2.get_yPosition() - p1.get_yPosition()) / double(p2.get_xPosition()-p1.get_xPosition()) ; 
    double b = p2.get_yPosition()-m *p2.get_xPosition(); 
    line_coefficients[0]=(m); 
    line_coefficients[1]=(1.0);
    line_coefficients[2]=(b);
    // line vector contains the coefficients of x,y,b respectively.
    cout<<"line is created and its coefficients: ! "<<endl ;
    for(int i=0;i<line_coefficients.size();i++){
        cout<<line_coefficients[i]<<" " ; 
    }
    cout<<endl ; 
    return line_coefficients; 
}
int get_position(vector<double> line ,vector <City*> city, int index){
    cout<<"Get position !"<<endl ; 
    // line: ax-by+c=0 where a is the first index of the line vector, b is the second and c is the third
    double position=0; 
    position= line[0] * city[index]->get_xPosition()+ line[2] ;
    position= position-city[index]->get_yPosition();
    // consider an arbitrary function that represents a line 
    // for instance for the graph 2x+1+y=0 
    // point (2,-1) is on the line
    // point (2,0) is above the line which can be visually confirmed, and by substituting the point into the equation
    // one can obtain ax+by+c >0 which is the met in the first if condition
    if(position<0){ 
        return +1 ;  // below the line 
    }
    else if (position>0){
        return -1 ; // above the line 
    }
    return 0 ; // position is initially 0, if it is on the line it satisfy the condition.  
}

string detect_cases(vector <double> line ,vector <City*> idx_hull, int index){

    cout<<"Detect case !"<<endl ; 
    cout<<"Current Node: "<<endl ;
    idx_hull[index%idx_hull.size()]->print_object();
    for(int i=0;i<idx_hull.size();i++){
        idx_hull[i]->print_object();
    }
    cout<<"Point next index: "<<(index+1) % idx_hull.size()<<endl ; 
    idx_hull[(index+1)%idx_hull.size()]->print_object(); 
    cout<<"Point prev: "<<endl ; 
    idx_hull[ (index-1+idx_hull.size())%idx_hull.size() + idx_hull.size() % idx_hull.size()]->print_object(); 
    int position_next = get_position( line,idx_hull,( (index+1) %idx_hull.size() )) ;
    int position_prev = get_position(line,idx_hull,( (index-1+idx_hull.size()) %idx_hull.size() ) ); 
    if((position_next ==1||position_next==0) && (position_prev == -1||position_prev==0) )
    {
        // next is above, prev is below, select next as pivot. 
        //cout<<"next"<<endl ;
        return "next"; 
    }
    else if ((position_next ==1||position_next==0) && (position_prev == 1 || position_prev==0) )
    {
        // both are above ; 
        //cout<<"Both are above "<<endl ; 
        return "lower_tangent"; 
    }
    else if ((position_next ==-1|| position_next==0) && (position_prev == +1|| position_prev==0))
    {
        // next is below, prev is above, select prev as pivot 
        //cout<<"Prev is above"<<endl ; 
        return "prev"; 
    }
    else if ((position_next ==-1|| position_next==0) &&(position_prev == -1|| position_prev==0))
    {
        // both are below 
        return "upper_tangent"; 
    }
    return "EXIT_SUCCESS" ; 
}
int find_right_most_index(const vector <City*> idx_hull){
    int temp=0 ; 
    for(int i=1 ;i<idx_hull.size();i++){
        if(idx_hull[i]->get_xPosition()>idx_hull[temp]->get_xPosition()){
            temp= i ;
        }
    }
    return temp; 
}
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
vector <City*> updated_combiner (vector <City*> &left_hull, vector<City*>right_hull){
    
    // first find right most point at the left hull
    // and left most point at the right hull 
    cout<<"welcome to the updated combiner "<<endl ; 
    int left_tangent_index= find_right_most_index(left_hull);
    int right_tangent_index= find_left_most_index(right_hull); 
    int size_left= left_hull.size();
    int size_right= right_hull.size(); 
    bool find_upper_tangent = false ;
    vector <City*> combined_hull  ;
    left_hull[left_tangent_index]->print_object(); 
    right_hull[right_tangent_index]->print_object(); 
    int iter=1;
    cout<<endl ; 
    int iter1= 0;
    int iter2= 0; 
    while(!find_upper_tangent){
        cout<<"Iteration:"<<iter<<endl ;  
        iter++; 
        find_upper_tangent=true; 
        while(updated_find_case(right_hull[right_tangent_index%size_right]
        ,left_hull[left_tangent_index%size_left],left_hull[(left_tangent_index+1+size_left)%size_left ])>=0)
        {
            cout<<"iter1: "<<iter1<<endl ;
            iter1 ++ ;
            left_tangent_index = (left_tangent_index+1+size_left)%size_left; 
            cout<<"knssjs"<<endl ;
        }
        while(updated_find_case(
            left_hull[left_tangent_index%size_left],right_hull[right_tangent_index%size_right],right_hull[(size_right+right_tangent_index-1)%size_right])<=0)
        {
            iter2 ++;
            right_tangent_index = (right_tangent_index+size_right-1)%size_right; 
            find_upper_tangent=false; 
        }
    }
    cout<<"Upper tangent is foundde !" <<endl ; 
    vector <int> upper_tangent_index(2); 
    upper_tangent_index[0]=left_tangent_index; 
    upper_tangent_index[1]= right_tangent_index ; 
    left_hull[left_tangent_index%size_left]->print_object(); 
    right_hull[right_tangent_index%size_right]->print_object(); 
    cout<<"TRY TO FIND LOWER TANGENT "<<endl ; 
    bool find_lower_tangent= false ;
    while(!find_lower_tangent){
        find_lower_tangent=true; 
        while(updated_find_case(left_hull[left_tangent_index],right_hull[right_tangent_index],
        right_hull[(right_tangent_index+1)%size_right])>=0){
            right_tangent_index= (right_tangent_index+1)%size_right; 

        }
        while(updated_find_case(right_hull[right_tangent_index],left_hull[left_tangent_index],
        left_hull[(left_tangent_index+size_left-1)%size_left])<=0){
            left_tangent_index= (size_left+left_tangent_index-1)%size_left ; 
            find_lower_tangent=false; 
        }
    }
    cout<<"LOWER TANGENT IS FOUND ! "<<endl ; 
    vector<int> lower_tangent_index(2);
    lower_tangent_index[0]= left_tangent_index; 
    lower_tangent_index[1]= right_tangent_index; 
    left_hull[lower_tangent_index[0]]->print_object();
    right_hull[lower_tangent_index[1]]->print_object();
    int index= upper_tangent_index[0]; 
    combined_hull.push_back(left_hull[index]); 
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
    cout<<"Print Combined Hull at the end :: : "<<endl ;
    for(int i=0;i<combined_hull.size();i++){
        combined_hull[i]->print_object(); 
    } 
    return combined_hull ;
}   



vector <City*> combiner(vector <City*>&left_hull ,vector<City*>&right_hull) {
    cout<<"hello!"<<endl ;
    vector <City*> combined_hull ;
    bool main_controller[2]= {true,true}; 
    bool loop_controller_right_hull=true; 

    // find the upper tangent ;
    int left_index_tangent= find_right_most_index(left_hull); 
    int right_index_tangent=find_left_most_index(right_hull);  
    cout<<"Print right most index: "<<endl ;
    left_hull[left_index_tangent]->print_object(); 
    cout<<"Print left most node :" << endl;
    right_hull[right_index_tangent]->print_object();
    cout<<"left Hull ! "<<endl ; 
    for(int i=0;i<left_hull.size();i++){
        cout<<left_hull[i]->get_xPosition()<<" " ; 
    }
    cout<<"Rigth Hall "<<endl  ; 
    for(int i=0;i<right_hull.size();i++){
        cout<<right_hull[i]->get_xPosition()<<" " ; 
    }
    vector <double> line ;
    cout<<"CHECK THE Upper tangent "<<endl ;
    while(main_controller[0] || main_controller[1]){
        // create line's equation: 
        cout<<"I want to create the line ! "<<endl ; 
        line = create_line(left_hull[left_index_tangent%left_hull.size()],right_hull[right_index_tangent%right_hull.size()]); 
        // first check the right halve
        // utilize the detect case method ! 
        if(loop_controller_right_hull)
        {
            string idx_case= detect_cases(line,right_hull,right_index_tangent); 
            if(idx_case== "next"){
                cout<<"next is above, prev is below "<<endl ; 
                cout<<"select next as pivot "<<endl ; 
                right_index_tangent+=1; 
                main_controller[0]= true; 
                main_controller[1]=true ;
            }
            else if(idx_case=="prev"){
                cout<<"Next is below, prev is above, select prev as pivot ! "<<endl ; 
                right_index_tangent-- ; 
                main_controller[0]= true;
                main_controller[1]=true; 
            }
            else if(idx_case=="lower_tangent"){
                cout<<"lower tangent is found !" <<endl ;
                right_index_tangent++; 
                main_controller[0]= true;
                main_controller[1]=true ;
            }
            else if(idx_case=="upper_tangent"){
                cout<<"Upper tangent is found !"<<endl ;
                cout<<"Look at the left half ! "<<endl ;
                loop_controller_right_hull=false; 
                main_controller[0]= false; 
            }
        }
        // if loop controller for the right hull is false, then loop controller for the left hull is true ! 
        else if(!loop_controller_right_hull){
                string current_case= detect_cases(line,left_hull,left_index_tangent);
                if(current_case=="next"){
                    cout<<"Next is above, prev is below !"<<endl ;
                    left_index_tangent+=1; 
                    main_controller[1]= true;
                    main_controller[0]=true;  
                }
                else if(current_case=="prev"){
                    cout<<"Prev is above, next is below ! "<<endl ;
                    left_index_tangent-- ; 
                    main_controller[1]=true ; 
                    main_controller[0]=true; 
                }
                else if(current_case=="lower_tangent"){
                    cout<<"Both are below ! "<<endl ;
                    left_index_tangent++;
                    main_controller[1]= true ; 
                    main_controller[0]=true; 
                }
                else if(current_case=="upper_tangent"){
                    cout<<"Upper tangent is found ! "<<endl ;
                    cout<<"Look at the right half "<<endl ;
                    loop_controller_right_hull=true;
                    main_controller[1]= false; 
                }
        }
    }
    // indexes for upper tangent are found
    // left_index_tangent; right_index_tangent; // indices at left and right hull vectors representing the points intersecting with the line
    cout<<"Upper tangent is successfully founded:"<<endl;
    left_hull[left_index_tangent]->print_object();
    right_hull[right_index_tangent]->print_object() ; 
    vector <int> upper_tangent_vector(2);
    upper_tangent_vector[0]=left_index_tangent; 
    upper_tangent_vector[1]=right_index_tangent;

    // find the lower tangent 
    main_controller[0]=true; 
    main_controller[1]= true; 
    loop_controller_right_hull=true;


    left_index_tangent= find_right_most_index(left_hull); 
    right_index_tangent= find_left_most_index(right_hull); 
    cout<<"right most index of the left hull: "<<endl ; 
    left_hull[left_index_tangent]->print_object();
    cout<<"left most idex of the right hull "<<endl ; 
    right_hull[right_index_tangent]->print_object() ; 

    vector <double> lower_tangent; 
    cout<<"TRY TO FIND LOWER TANGENT "<<endl ; 
    cout<<"********************************************************"<<endl ; 
    int done= 0 ;

    while(main_controller[0] || main_controller[1]){
        // create line's equation: 
        cout<<"Create the lower Tangent: "<<endl ;
        lower_tangent=create_line(left_hull[left_index_tangent%left_hull.size()],right_hull[right_index_tangent%right_hull.size()]); 
        // first check the right halve
        // utilize the detect case method ! 
        if(loop_controller_right_hull)
        {
            string idx_case_lower= detect_cases(lower_tangent,right_hull,right_index_tangent) ;
            if(idx_case_lower== "next"){
                cout<<"next is above, prev is below "<<endl ; 
                cout<<"select prev as pivot "<<endl ; 
                right_index_tangent--; 
                main_controller[0]= true; 
                main_controller[1]=true ; 
            }
            else if(idx_case_lower=="prev"){
                cout<<"Next is below, prev is above, select next as pivot ! "<<endl ; 
                right_index_tangent++ ; 
                main_controller[0]= true;
                main_controller[1]=true ; 
            }
            else if(idx_case_lower=="lower_tangent"){
                cout<<"lower tangent is found !" <<endl ;
                cout<<"Look at the left half !"<<endl ; 
                loop_controller_right_hull=false; 
                main_controller[0]=false; 
            }
            else if(idx_case_lower=="upper_tangent"){
                cout<<"Upper tangent is found !"<<endl ;
                right_index_tangent++; 
                main_controller[0]= true;
                main_controller[1]=true ; 
            }
        }
        // if loop controller for the right hull is false, then loop controller for the left hull is true ! 
        else if(!loop_controller_right_hull){
            string idx_case_lower_left= detect_cases(lower_tangent,left_hull,left_index_tangent);
                if(idx_case_lower_left=="next"){
                    cout<<"Next is above, prev is below !"<<endl ;
                    left_index_tangent-=1; 
                    main_controller[0]=true ;
                    main_controller[1]= true; 
                }
                else if(idx_case_lower_left=="prev"){
                    cout<<"Prev is above, next is below ! "<<endl ;
                    left_index_tangent++ ; 
                    main_controller[0]=true; 
                    main_controller[1]=true ; 
                }
                else if(idx_case_lower_left=="lower_tangent"){
                    cout<<"Both are above ! "<<endl ;
                    cout<<"lower tangent is found !" <<endl ;
                    cout<<"Look at the right half !"<<endl ; 
                    loop_controller_right_hull=true; 
                    main_controller[1]=false;  
                }
                else if(idx_case_lower_left=="upper_tangent"){
                    cout<<"Upper tangent is found ! "<<endl ;
                    cout<<"iterate again !" <<endl ; 
                    left_index_tangent++;
                    main_controller[0]=true ;
                    main_controller[1]= true ;
                }
        }
        cout<<"İterations ends here "<<endl ;
    }
    // indexes for lower tangent is found ! 
    vector <int> lower_tangent_vector(2);
    lower_tangent_vector[0]= ((left_index_tangent+left_hull.size())%left_hull.size()) ;
    lower_tangent_vector[1]= right_index_tangent; 
    cout<<"LOWER TANGENT FOUND !"<<endl ;
    cout<<"****************************************"<<endl ; 
    cout<<"Info of the tangents: "<<endl ; 
    cout<<"CHECKED LOWER AND UPPER TANGENTS CAN BE FOUNDED PROPERLY ! "<<endl ; 

    left_hull[upper_tangent_vector[0]]->print_object();
    right_hull[upper_tangent_vector[1]]->print_object(); 
    left_hull[left_index_tangent%left_hull.size()]->print_object();
    right_hull[right_index_tangent]->print_object();

    // we want to obtain the path counterclockwise. 
    // so start from left index of the upper tangent and add up to the vector
    // until the left index of the lower tangent is intersected.
    int index=upper_tangent_vector[0];
    cout<<"Upper left Node: "<<endl ; 
    left_hull[index%left_hull.size()]->print_object();
    combined_hull.push_back(left_hull[index %left_hull.size()]); // start from upper left 
    cout<<"combined hull push loop"<<endl ;
    cout<<"Lower tangent vector"<<lower_tangent_vector[0]<<endl ;
    while(index != lower_tangent_vector[0]) {
        index= ((index+1)%left_hull.size() ); 
        combined_hull.push_back(left_hull[index]);
    }   
    cout<<endl ; 
    index= lower_tangent_vector[1]; 
    combined_hull.push_back(right_hull[index%right_hull.size()]);
    while(index!=upper_tangent_vector[1]){
        index= (index+1)%right_hull.size(); 
        combined_hull.push_back(right_hull[index]); 
    }
    cout<<"Print Combined Hull at the end :: : "<<endl ;
    for(int i=0;i<combined_hull.size();i++){
        combined_hull[i]->print_object(); 
    }
    // exit(0); 
    return combined_hull; 
}
    

vector<City*> seperater(vector <City*> city_vector ) {
    // initialize the vector of pointer to objects for left and right halves;

    if (city_vector.size()<=3){
        cout<<"BASE CASE !"<<endl ; 
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
    cout<<"print left" <<endl ; 
    for(int i=0;i<left.size();i++){
        left[i]->print_object(); 
    }
    cout<<"print right "<<endl ; 
    for(int i=0;i<right.size();i++){
        right[i]->print_object(); 
    }
    cout<<"Here Left"<<endl; 
    left = seperater(left); 
    cout<<"Here Right"<<endl ; 
    right= seperater(right); 
    cout<<"now combiner"<<endl ; 

    //return combiner(left,right); 
    return updated_combiner(left,right); 
} 

// Method to read the file, create the content vector and create the vector of objects to pointers using the content
vector<City*> read_file(string file_name,int* num_bakeryp,float* thresholdp,int* source_bakeryp,int* target_bakeryp){
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
    int source_index_bakery=0;
    int target_index_bakery=0;
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
            }
            else if(row_counter==1){
                if(col_counter==0){
                    cout<<"No city: "<<no_city << " No bakery: "<<no_bakery<<" Threshold: "<<threshold<<endl  ;
                }
                if(col_counter==0) source_index_bakery=stoi(column); 
                else if(col_counter==1){
                    target_index_bakery=stoi(column); 
                    cout<<"Source Index:" <<source_index_bakery<<" Target Index: "<<target_index_bakery<<endl;
                }
            }
            else {
                    row[row_counter-2][col_counter]= stoi(column); 
            }
            col_counter+=1 ; 
        }
        row_counter+=1;
    }    
    return create_object(row); 
}
bool comparison(City * cityp1, City* cityp2) {
    return cityp1->get_xPosition()< cityp2->get_xPosition(); 
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
    int* source_bakeryp=new int[1];
    int* target_bakeryp= new int[1]; 
    vector <City*> city_vector= read_file(file_name,num_cityp,thresholdp,source_bakeryp,target_bakeryp);
    // sort the vector by X using compare by x function, it returns true
    // if x of the first element is smaller than the second
    cout<<"CHECK WHETHER THE DATA IS EXTRACTDE PROPERLY! "<<endl ; 
    for(int i=0;i<city_vector.size();i++){
        city_vector[i]->print_object(); 
    } 
    sort(city_vector.begin(), city_vector.end(), comparison);
    cout<<"Check the sorted Version !" <<endl ; 
    for(int i=0;i<city_vector.size();i++){
        city_vector[i]->print_object(); 
    } 
    vector<City*> vector = seperater(city_vector);
    cout<<("*************************-----------------------------------------")<<endl ; 
    for(int i=0;i<vector.size();i++){
        vector[i]->print_object();
    }
    int no_city= *num_cityp; 
    float threshold= *thresholdp;  
    int source_index_bakery=*source_bakeryp;
    int target_index_bakery=*target_bakeryp;
    cout<<"No city: "<<no_city<<" ,Threshold: "<<threshold
    <<" ,Source Index Bakery: "<<source_index_bakery<<" ,Target Index Bakery: "<<target_index_bakery<<endl ;
    delete [] num_cityp;
    num_cityp=nullptr; 
    delete [] thresholdp ; 
    thresholdp= nullptr; 
    delete [] source_bakeryp;
    source_bakeryp=nullptr; 
    delete [] target_bakeryp; 
    target_bakeryp= nullptr ; 
    exit(0);
}