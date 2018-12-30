//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

//Erorr : invalid command (First character not matching )
bool valid(string cmnd){
	for (int i=0;i<=6;i++){
		if(cmnd== keyWordsList[i]){
			return true;
		}
	}
	// If nothing matches it returns false
	return false;
}

//Error: invalid arguement (parameter is of a wrong type)

bool paramTypeCheck(string input){
	stringstream lin(input);
	string cmnd;
	lin>>cmnd;
	
	//Parameter should not be checked if value has not been inputed, therfore we need to peek 
	//and verify that its not a space. We also need to verify eof() is not triggered
	
	if(cmnd=="create"){
		string n_input,t_input;
		int x_loc,y_loc,x_sz,y_sz;
		lin>>n_input;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){ 
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		lin>>t_input;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
		}
		lin>>x_loc;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		lin>>y_loc;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		lin>>x_sz;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		lin>>y_sz;
		if(lin.fail() || (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
		}
		return true;
	}
	if(cmnd=="move"){
		string name; 
		int x_loc,y_loc;
		lin>>name;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		lin>>x_loc;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		lin>>y_loc;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		return true;
	}
	if(cmnd=="rotate"){
		string name; 
		int angle;
		lin>>name;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		lin>>angle;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		return true;
	}
	if(cmnd=="draw" || cmnd=="delete"){
		string name;
		lin>>name;
		if(lin.fail()|| (!lin.eof()&&lin.peek()!=' ')){
			if(lin.eof())
				return true;
			else
				return false;
			
		}
		return true;
	}
}

//Error : invalid shape name (input shape name is a reserved keyword)

bool checkShapeName(string shape){
	stringstream in_1(shape);
	string a;
	in_1>>shape;
	if(in_1.fail())
		return true;
	for(int i=0;i<=6;i++){
		if(shape==keyWordsList[i])
			return false;
	}
	for(int i=0;i<=2;i++){
		if(shape==shapeTypesList[i])
			return false;
	}
	return true;
}

//Error : shape name exists (input shape name has already been used)

bool checkNotDuplicate(string shape){
	for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL){
			string name = shapesArray[i]->getName();
			if(shape==name)
				return false;
		}
	}
	return true;
}

//Error: shape name not found (input shape name does not exist)

bool findShape(string name){
	stringstream in_2(name);
	in_2>>name;
	for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL){
			string n = shapesArray[i]->getName();
			if(name==n)
				return true;
		}	
	}
	if(in_2.fail())
		return true;
	return false;
}

//Error: invalid shape type (input hspae type is not one of the pre defined shape types)

bool checkShapeType (string type){
	stringstream in(type);
	string a;
	in>>type;
	bool check = false;
	for(int i=0;i<=2;i++){
			if(type==shapeTypesList[i])
				check = true;
	}
	if(in.fail())
		check=true;
	return check;
}

//Error: invalid value (value of loc is less than 0 or value of rotation is not b/w 0 and 360)

bool checkValue(string cmnd,int value){
		if(cmnd == "rotate"){
			if(value<0 || value>360)
				return false;
		}
		if(value<0)
			return false;
	return true;
}

//Erorr : too many parameters (number of requirements is more than required)

bool moreParameters(string input){
	stringstream lin_1(input);
	string cmnd;
	lin_1>>cmnd;
	if(cmnd=="create"){
		string n_input,t_input;
		int x_loc,y_loc,x_sz,y_sz;
		lin_1>>n_input;
		lin_1>>t_input;
		lin_1>>x_loc;
		lin_1>>y_loc;
		lin_1>>x_sz;
	    lin_1>>y_sz;
		
		//if number of parameters are correct, the while loop will not be executed
		while(!lin_1.eof()){
		 char a;
		 lin_1>>a;
		 if(a!='\t'&& a!='\0')
			return false;
		}
		return true;
	}
	if(cmnd=="move"){
			string name; 
			int x_loc,y_loc;
			lin_1>>name>>x_loc>>y_loc;
		
			while(!lin_1.eof()){
				char a;
			lin_1>>a;
			if(a!='\t'&& a!='\0')
				return false;
			}
			return true;
		}
	if(cmnd=="rotate"){
		string name; 
		int angle;
		lin_1>>name>>angle;
		while(!lin_1.eof()){
			char a;
			lin_1>>a;
			if(a!='\t'&& a!='\0')
				return false;
		}
		return true;
	}
	if(cmnd=="draw"|| cmnd=="delete"){
		string name; 
		lin_1>>name;
		while(!lin_1.eof()){
			char a;
			lin_1>>a;
			if(a!='\t'&& a!='\0')
				return false;
		}
		return true;
	}
}

//Erorr : too parameters (number of requirements is lesser than required)

bool fewParameters(string input){
	stringstream lin_2(input);
	string cmnd;
	lin_2>>cmnd;
	if(cmnd=="create"){
		string n_input,t_input;
		int x_loc,y_loc,x_sz;
		if(lin_2.eof())
			return false;
		lin_2>>n_input;
		if(lin_2.eof())
			return false;
		lin_2>>t_input;
		if(lin_2.eof())
			return false;
		lin_2>>x_loc;
		if(lin_2.eof())
			return false;
		lin_2>>y_loc;
		if(lin_2.eof())
			return false;
		lin_2>>x_sz;
		if(lin_2.eof())
			return false;
		return true;
	}
	if(cmnd=="move"){
		string name; 
		int x_loc;
		if(lin_2.eof())
			return false;
		lin_2>>name;
		if(lin_2.eof())
			return false;
		lin_2>>x_loc;
		if(lin_2.eof())
			return false;
		return true;
	}
	if(cmnd=="rotate"){
		string name; 
		if(lin_2.eof())
			return false;
		lin_2>>name;
		if(lin_2.eof())
			return false;
		return true;
	}
	if(cmnd=="draw"|| cmnd=="delete"){
		if(lin_2.eof())
			return false;
		return true;
	}
}

//Error : shape array is full

bool  checkMax(){
	if(shapeCount == max_shapes)
		return false;
	return true;
}

//Creates shape
void create(string input){
	stringstream createInput(input);
	string n_user,t_user,cmnd;
	createInput>>cmnd;
	int xloc,yloc,xsize,ysize;
	createInput>>n_user>>t_user>>xloc>>yloc>>xsize>>ysize;
	shapesArray[shapeCount] = new shape(n_user,t_user,xloc,yloc,xsize,ysize);
	cout<<"Created "<<shapesArray[shapeCount]->getName()<<": "<<shapesArray[shapeCount]->getType();
	cout<<" "<<shapesArray[shapeCount]->getXlocation()<<" "<<shapesArray[shapeCount]->getYlocation();
	cout<<" "<<shapesArray[shapeCount]->getXsize()<<" "<<shapesArray[shapeCount]->getYsize()<<endl;
	shapeCount++;
	
}

//Moves shape to a specific location
void moveShape(string name,int xloc,int yloc){
	for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL && shapesArray[i]->getName()== name)
			shapesArray[i]->setXlocation(xloc);
			shapesArray[i]->setYlocation(yloc);
			cout<<"Moved "<<shapesArray[i]->getName()<<" to "<<shapesArray[i]->getXlocation()<<" "<<shapesArray[i]->getYlocation()<<endl;
	}
}

//Rotates Shape
void rotateShape(string name,int angle){
	for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL && shapesArray[i]->getName()== name)
			shapesArray[i]->setRotate(angle);
			cout<<"Rotated "<<shapesArray[i]->getName()<<" by "<<angle<<" degrees"<<endl;
	}
}

//Draws a shape/draws all shapes
void drawShape(string name){
	if(name=="all"){
		cout<<"Drew all shapes"<<endl;
		for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL)
			shapesArray[i]->draw();
		}
	}
	else{
		for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL && shapesArray[i]->getName()== name){
			cout<<"Drew"<<" "<<shapesArray[i]->getName()<<endl; 
			shapesArray[i]->draw();
		}
	}
	}
}

//Deletes a shpe/deletes all shapes
void deleteShape(string name){
	if(name=="all"){
		cout<<"Deleted: all shapes"<<endl;
		for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL)
			delete (shapesArray[i]);
			shapesArray[i] = NULL;
		}
	}
	else{
		for(int i=0;i<shapeCount;i++){
		if(shapesArray[i]!=NULL && shapesArray[i]->getName()== name){
			cout<<"Deleted shape"<<" "<<shapesArray[i]->getName()<<endl; 
			delete (shapesArray[i]);
			shapesArray[i] = NULL;
		}
	}
	}
}


int main() {
    string line;
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
	   string command;
        // Put the line in a linestream for parsing15:13:37: Symbols file loaded into OS file system cache (0 seconds)

        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
		if(valid(command)){
			
			if(command == "maxShapes"){
				lineStream>> max_shapes;
				shapesArray = new shape* [max_shapes];
				cout<<"New database: max shapes is "<<max_shapes<<endl;
			}
			
			if(command == "create"){
				string n_user,t_user;
				int xloc,yloc=0,xsize=0,ysize=0;
				lineStream>>n_user>>t_user>>xloc>>yloc>>xsize>>ysize;
				if(checkShapeName(n_user)){
					if(checkNotDuplicate(n_user)){
						if(checkShapeType(t_user)){
							if(paramTypeCheck(line)){
								if(checkValue(command,xloc)&&checkValue(command,yloc)&&
								   checkValue(command,ysize)&&checkValue(command,ysize)){
									   if(moreParameters(line)){
										   if(fewParameters(line)){
											   if(checkMax())
													create(line);
												else
													cout<<"Error: shape array is full"<<endl;
										   }
										   else
											   cout<<"Error: too few arguments"<<endl;
									   }
									   else
										   cout<<"Error: too many arguments"<<endl;
								}
								else
									cout<<"Error: invalid value"<<endl;
							}
							else
								cout<<"Error: invalid argument"<<endl;  
						}
						else
							cout<<"Error: invalid shape type"<<endl; 
					}
					else
						cout<<"Error: shape name exists"<<endl;
				}
				else 
					cout<<"Error: invalid shape name"<<endl;
			}
			
			if(command =="move"){
				string name;
				int xloc,yloc;
				lineStream>>name>>xloc>>yloc;
				if(checkShapeName(name)){
					if(findShape(name) ){
						if(paramTypeCheck(line)){
							if(checkValue(command,xloc) && checkValue(command,yloc)){
								if(moreParameters(line)){
									if(fewParameters(line)){
										moveShape(name,xloc,yloc);
									}
									else
										cout<<"Error: too few arguments"<<endl;
								}
								else
									cout<<"Error: too many arguments"<<endl;								 
							}
							else
								cout<<"Error: invalid value"<<endl;
						}
						else
							cout<<"Error: invalid argument"<<endl;
					}
					else
						cout<<"Error: shape "<<name<< " not found"<<endl;
				}
				else
					cout<<"Error: invalid shape name"<<endl;
			}
			
			if(command =="rotate"){
				string name;
				int angle;
				lineStream>>name>>angle;
				if(checkShapeName(name)){
					if(findShape(name) ){
						if(paramTypeCheck(line)){
							if(checkValue(command,angle)){
								if(moreParameters(line)){
									if(fewParameters(line)){
										rotateShape(name,angle);
									}
									else
										cout<<"Error: too few arguments"<<endl;
								}
								else
									cout<<"Error: too many arguments"<<endl;								 
							}
							else
								cout<<"Error: invalid value"<<endl;
						}
						else
							cout<<"Error: invalid argument"<<endl;
					}
					else
						cout<<"Error: shape "<<name<< " not found"<<endl;
				}
				else
					cout<<"Error: invalid shape name"<<endl;
			}
			
			if(command == "draw"|| command=="delete"){
				string name;
				lineStream>>name;
				if(paramTypeCheck(line)){
					if(checkShapeName(name) || name=="all"){
						if(findShape(name)|| name=="all"){
								if(moreParameters(line)){
									if(fewParameters(line)){
										if(command == "draw")
											drawShape(name);
										else
											deleteShape(name);
									}
									else
										cout<<"Error: too few arguments"<<endl;
								}
								else
									cout<<"Error: too many arguments"<<endl;								 
						}
						else
							cout<<"Error: shape "<<name<< " not found"<<endl;
					}
					else
						cout<<"Error: invalid shape name"<<endl;
				}
				else
					cout<<"Error: invalid argument"<<endl;
			}
		}
		else{
			cout<<"Error: invalid command"<<endl;
		}
		
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

