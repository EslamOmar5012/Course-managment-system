#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>

using namespace std;
int s_id;
const int LINE_TO_FIND = 2;
int j;
bool admin_loop;
bool student_loop;
int marks[11][11];
int marks_stud_id[12];
int marks_course_id[12];
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);// <=========== For coloring the console text

struct Course {


	string name;
	int id;
	string students_names[10];
	int number_of_enrolled;
	int id_of_student_enrolled[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	int marks_of_students[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };


}Courses[20];

struct Student {


	int Id;
	string username;
	string password;
	Course Courses_enrolled[20];
	int number_of_courses_enrolled = 0;


}Students[20];
bool existss = false;
bool Find_Item(int arr[], int size, int searcheditem) {   // search inside array for integer
	for (int i = 0; i < size; i++) {
		if (arr[i] == searcheditem)
			existss = true;
	}
	return existss;
}
void program_details() {
	system("CLS");

	cout << "\n\n\n\t\t\t\t\t\t\t\t\t                       _       _                             _        o          \n";
	cout << "\t\t\t\t\t\t\t\t\t|V| _  __ _     o __ _|_ _    |_||_  _    _|_   _|_|_  _    |_) __ _  |  _  _ _|_\n";
	cout << "\t\t\t\t\t\t\t\t\t| |(_) | (/_    | | | | (_)   | ||_)(_)|_| |_    |_| |(/_   |   | (_)_| (/_(_  |_\n\n";

	string arr[4] = { "\t\t\t\t\t\t\t\t\tfaculty : ASU-fcis \n" , "\t\t\t\t\t\t\t\t\tNames : Eslam Monir \t\t 20201700115 \n \t\t\t\t\t\t\t\t\t\tEslam magdy \t\t 20201700121 \n \t\t\t\t\t\t\t\t\t\tEslam Omar \t\t 20201700120 \n\t\t\t\t\t\t\t\t\t\tAzdashir Mohamed\t 20201700104 \n \t\t\t\t\t\t\t\t\t\tAhmed Mohamed \t\t 20201700075 \n \t\t\t\t\t\t\t\t\t\tZiad Khaled \t\t 20201700304 \n \t\t\t\t\t\t\t\t\t\tAhmed Samir \t\t 20201700047 \n","\t\t\t\t\t\t\t\t\tVersion : 1.0.7 \n" , "\t\t\t\t\t\t\t\t\tCups of tea Consumed : 51 \n" };
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			SetConsoleTextAttribute(h, 3);
		else if (i == 1)
			SetConsoleTextAttribute(h, 14);
		else if (i == 2)SetConsoleTextAttribute(h, 8);
		else SetConsoleTextAttribute(h, 15);
		cout << *(arr + i) << endl;

	}
	system("pause");
}

void Fetch_marks() { // <============== Puts the marks from file into a 2D array 
	ifstream Marks("Marks.txt");


	for (int i = 0; i < 12; i++)
	{

		for (int j = 0; j < 12; j++)
		{
			Marks >> marks[i][j];// <============== 1'st index in the array for Student id  2'nd index for Course id

		}

	}
}

void Edit_Marks(int stud_id) {// <============= Edits the marks from the array and then Puts it in the file by overwriting it
	int x, y, z;
	x = stud_id;
	SetConsoleTextAttribute(h, 3); // <============== Colors text below to Blue (ID of blue is 3)
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tEnter Course ID : ";
	SetConsoleTextAttribute(h, 15);// <============== Colors text below to white (ID of white is 15)
	cin >> y;
	SetConsoleTextAttribute(h, 3);
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tEnter Mark : ";
	SetConsoleTextAttribute(h, 15);
	cin >> z;
	Fetch_marks();// <============= Puts marks in the array
	marks[x][y] = z;
	ofstream Marks("Marks.txt");


	for (int i = 0; i < 12; i++) {    // <=========== overwrites the file with new mark

		for (int j = 0; j < 12; j++) {

			Marks << marks[i][j] << " ";
		}
		Marks << endl;
	}
	Marks.close();
}

void Fetch_Data() { // <============= Puts all the data in The files into its structs (Students / Courses) 
					//                Also counts the number of courses the student is enrolled in and then puts the count in number_of_courses_enrolled 

	for (int id = 0; id < 10; id++) {

		for (int j = 0; j <= 10; j++) {

			Students[id].Courses_enrolled[j].id = -1;

		}
	}

	int last = 0;

	for (int ID = 0; ID <= 10; ID++) { // <=========== Puts students data in its structs
		//Student file entry

		string filename = "Student" + to_string(ID) + ".txt";
		ifstream student_info("Students_file/" + filename);

		while (student_info >> Students[ID].Id >> Students[ID].username >> Students[ID].password >> Students[ID].number_of_courses_enrolled >> Students[ID].Courses_enrolled[0].id >> Students[ID].Courses_enrolled[1].id >> Students[ID].Courses_enrolled[2].id >> Students[ID].Courses_enrolled[3].id >> Students[ID].Courses_enrolled[4].id >> Students[ID].Courses_enrolled[5].id >> Students[ID].Courses_enrolled[6].id >> Students[ID].Courses_enrolled[7].id >> Students[ID].Courses_enrolled[8].id >> Students[ID].Courses_enrolled[9].id >> Students[ID].Courses_enrolled[10].id) {}

		if (Students[ID].username.size() > 2) {
			last = Students[ID].Id + 1;
		}
	}

	int courseNum = 0;
	int j = 0;
	bool is_here = false;

	for (int ID = 0; ID < 10; ID++) { // <=========== Puts courses data in its Structs

		string File_name = "Course" + to_string(ID) + ".txt";
		fstream File("Courses_file/" + File_name);

		if (File) {


			File >> Courses[ID].id >> Courses[ID].name >> Courses[ID].number_of_enrolled;

			for (int i = 0; i <= 9; i++) {

				File >> Courses[ID].id_of_student_enrolled[i];

			}
		}

	}

	for (int ID = 0; ID < 10; ID++) { // <================ Counts how many courses every student is enrolled in

		Students[ID].number_of_courses_enrolled = 0;


		for (int i = 0; i <= 10; i++) {


			if (Students[ID].Courses_enrolled[i].id != -1)
				Students[ID].number_of_courses_enrolled++;

		}

	}

	for (int ID = 0; ID < last; ID++) {// <========== after counting the number of courses enrolled this loop overwrites the file with the new count

		string filename = "Student" + to_string(ID) + ".txt";
		ofstream file("Students_file/" + filename);

		file << Students[ID].Id << " " << Students[ID].username << " " << Students[ID].password << " " << Students[ID].number_of_courses_enrolled << " \n";

		file.close();

		bool s = true;
		int i = 0;

		file.open(("Students_file/" + filename), ios_base::app);

		for (int i = 0; i < Students[ID].number_of_courses_enrolled; i++) {

			file << Students[ID].Courses_enrolled[i].id << " ";
		}

		file.close();
	}

}

bool  Admin_Or_User() // <============ Asks the User if he is an Admin or a Studemt
{
	string x;
	bool type = false;





	{ SetConsoleTextAttribute(h, 6);
	cout << "\n\n\n\n\n\t  ___________________________________________________________________________________________________________________________________________________________________________________________________\n";
	SetConsoleTextAttribute(h, 3);
	printf("\t\t   ____                                                                                                                       _       ____                  _                        \n");
	printf("\t\t  / ___|   ___    _   _   _ __   ___    ___     _ __ ___     __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    / ___|   _   _   ___  | |_    ___   _ __ ___    \n");
	printf("\t\t | |      / _ \\  | | | | | '__| / __|  / _ \\   | '_ ` _ \\   / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|   \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\   \n");
	printf("\t\t | |___  | (_) | | |_| | | |    \\__ \\ |  __/   | | | | | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ___) | | |_| | \\__ \\ | |_  |  __/ | | | | | |  \n");
	printf("\t\t  \\____|  \\___/   \\__,_| |_|    |___/  \\___|   |_| |_| |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|  \n");
	printf("\t\t                                                                                    |___/                                                     |___/                                  \n");
	SetConsoleTextAttribute(h, 6);
	cout << "\t  ___________________________________________________________________________________________________________________________________________________________________________________________________";
	SetConsoleTextAttribute(h, 15);
	cout << "\n\tBY: ";
	SetConsoleTextAttribute(h, 8);
	cout << "   |---:: Eslam Monir ::---|  |---:: Eslam Magdy ::---|  |---:: Eslam Omar ::---|  |---:: Azdasher Mohamed ::---|  |---:: Ziad Khaled ::---|  |---:: Ahmed Raoof ::---|  |---:: Ahmed Samir ::---|";
	}





	SetConsoleTextAttribute(h, 3);
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\t Are You an Admin or an Student?: \n\t\t\t\t\t\t\t\t\t\t\t\t\t    ";


	do {

		SetConsoleTextAttribute(h, 15);
		cin >> x;


		if (x == "Admin")

			type = true;

		else if (x != "Admin" && x != "Student") {
			SetConsoleTextAttribute(h, 4);
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tInvalid Input: ";
		}

	} while ((x != "Admin") && (x != "Student"));

	return type;
}

int Entry_Check(bool y)// <=========== takes the user name and passwords of Admins or Students and then verifies it
{
	string username;
	string password;
	string Username;
	string Password;

	bool is_found = false;
	int z = -2;
	bool right = true;

	if (y == true)
	{


		do {
			SetConsoleTextAttribute(h, 3);
			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tEnter username and password \n";

			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tUsername: ";

			SetConsoleTextAttribute(h, 15);
			cin >> username;

			cout << "\n";

			SetConsoleTextAttribute(h, 3);
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tPassword: ";

			SetConsoleTextAttribute(h, 15);
			cin >> password;

			if (username == "Admin" && password == "admin123")


				z = -1;

			else
			{
				SetConsoleTextAttribute(h, 4);
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tInvalid Input ";
			}

		} while ((username != "Admin") || (password != "admin123"));


		system("CLR");
	}
	else
	{

		do {
			SetConsoleTextAttribute(h, 3);
			cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tEnter username and password \n";

			cout << "\t\t\t\t\t\t\t\t\t\t\t\tUsername: ";

			SetConsoleTextAttribute(h, 15);
			cin >> Username;
			cout << "\n";

			for (int i = 0; i < 20; i++) {
				if (Username == Students[i].username) {
					s_id = Students[i].Id;
				}
			}

			SetConsoleTextAttribute(h, 3);
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tPassword: ";

			SetConsoleTextAttribute(h, 15);
			cin >> Password;

			for (int i = 0; i <= 10; i++) {

				if (Username == Students[i].username && Password == Students[i].password) {
					is_found = true;
					z = Students[i].Id;


					break;
				}


			}
		} while (is_found == false);






	}

	return z;





}

//Students secton
void Student_Creation() // <========== Creates a Student file and puts it in a struct
{
	string y, z;
	int number_of_student;


	for (int ID = 0; ID < 20; ID++)
	{
		string filename = "Student" + to_string(ID) + ".txt";

		ifstream student_info("Students_file/" + filename);
		if (!student_info)
		{
			number_of_student = ID;
			break;
		}





	}

	string filename = "Student" + to_string(number_of_student) + ".txt";
	ofstream student_insert("Students_file/" + filename);

	SetConsoleTextAttribute(h, 6);
	Students[number_of_student].Id = number_of_student;

	cout << "\n\n\n\t\t\t __                         __                   \n";
	cout << "\t\t\t/   __ _  _ _|_ _     _    (_ _|_    _| _ __ _|_\n";
	cout << "\t\t\t\\__ | (/_(_| |_(/_   (_|   __) |_|_|(_|(/_| | |_\n";

	SetConsoleTextAttribute(h, 3);
	cout << "\t\t\t";


	cout << "\n\t\t\t    Please enter username: ";

	SetConsoleTextAttribute(h, 15);
	cin >> Students[number_of_student].username;



	SetConsoleTextAttribute(h, 3);
	cout << "\n\t\t\t    Please enter password: ";

	SetConsoleTextAttribute(h, 15);
	cin >> Students[number_of_student].password;


	student_insert << Students[number_of_student].Id << " " << Students[number_of_student].username << " " << Students[number_of_student].password << " 0";


	Fetch_Data();
}

void Student_Info(int id) {//<============= Shows the admin the info of the student
	Fetch_Data();
	system("CLS");
	SetConsoleTextAttribute(h, 6);
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t\tStudent id : " << Students[id].Id << " \t\t" << "Student name : " << Students[id].username << "\n\t\t\t\t\t\t\t\t\t\t____________________________________\n\n";


	for (int i = 0; i < 10; i++) {

		if ((Students[id].Courses_enrolled[i].id != -1)) {

			SetConsoleTextAttribute(h, 3);
			cout << "\t\t\t\t\t\t\t\t\t\t" << Courses[Students[id].Courses_enrolled[i].id].name << "                  Mark: " << marks[id][Students[id].Courses_enrolled[i].id] << "\n\n";


			SetConsoleTextAttribute(h, 6);
			cout << "\t\t\t\t\t\t\t\t\t\t_______________________________________________________________\n";


		}
		else

			break;

	}
}

int Student_Enroll(int) // <================ returns the id of the Course the student want to enroll in to pass Add_Course() function
{
	int Match = 0;
	int courseNum = 0;
	int j = 0;
	bool is_here = false;

	for (int ID = 0; ID < 20; ID++) {
		string File_name = "Course" + to_string(ID) + ".txt";
		fstream File("Courses_file/" + File_name);
		if (File) {
			File >> Courses[ID].id >> Courses[ID].name >> Courses[ID].number_of_enrolled >> Courses[ID].id_of_student_enrolled[0] >> Courses[ID].id_of_student_enrolled[1] >> Courses[ID].id_of_student_enrolled[2] >> Courses[ID].id_of_student_enrolled[3] >> Courses[ID].id_of_student_enrolled[4] >> Courses[ID].id_of_student_enrolled[5] >> Courses[ID].id_of_student_enrolled[6] >> Courses[ID].id_of_student_enrolled[7] >> Courses[ID].id_of_student_enrolled[8] >> Courses[ID].id_of_student_enrolled[9];
		}
	}

	system("CLS");
	SetConsoleTextAttribute(h, 6);
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\tEnrollable Courses:\n\n\n\t\t\t\t\t\t\t\t\t\t\t_______________________________________ ";

	for (int i = 0; i < 20; i++) {
		if (Courses[i].id == i) {
			SetConsoleTextAttribute(h, 3);
			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t Course ID: ";
			SetConsoleTextAttribute(h, 8);
			cout << Courses[i].id;
			SetConsoleTextAttribute(h, 3);
			cout << "      Course Name:  ";
			SetConsoleTextAttribute(h, 8);
			cout << Courses[i].name << "\n";
		}
		else
			break;
	}

	do {
		Match = 0;
		SetConsoleTextAttribute(h, 8);
		cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter the course ID : ";
		cin >> courseNum;
		for (int i = 0; i <= 20; i++) {
			if (s_id == Courses[courseNum].id_of_student_enrolled[i]) {
				Match++;
			}
		}
		if (Match > 0) {
			SetConsoleTextAttribute(h, 4);
			cout << "\n\t\t\t\t\t\t\t\t\t\t\tStudent is enrolled in this course.\n";
		}
		else {
			if (courseNum == 0) {
				Courses[j].id = 0;
				is_here = true;
			}
			else {
				for (int j = 0; j < 10; j++) {
					if (Courses[j].id == courseNum) {
						cout << courseNum << "\n";
						is_here = true;
					}
				}
			}
		}
	} while (is_here == false);

	return courseNum;
}

void Student_Edit(int stud_id)// <============== Edits Username of selected Student
{
	int id;
	string location;

	id = stud_id;


	while (true) {

		location = "Student" + to_string(id) + ".txt";
		ifstream Student_checkfile("Students_file/" + location);

		if (Student_checkfile)
			break;

		SetConsoleTextAttribute(h, 4);
		cout << "\n\t\t\t\t\t\t\t\t\t\t\tThe Id you entered not exist" << endl << "\n\t\t\t\t\t\t\t\t\t\t\tPlease enter the right id" << endl;
	}
	ifstream Student_checkfile("Students_file/" + location);

	SetConsoleTextAttribute(h, 3);
	cout << "\n\t\t\t\t\t\t\t\t\t\t\tPlease enter new username: ";

	SetConsoleTextAttribute(h, 15);
	cin >> Students[id].username;

	ofstream Student_file("Students_file/" + location);

	Student_file << id << " " << Students[id].username << " " << Students[id].password << " " << Students[id].number_of_courses_enrolled << endl;

	for (int i = 0; i < Students[id].number_of_courses_enrolled; i++) {

		Student_file << Students[id].Courses_enrolled[i].id << Students[id].Courses_enrolled[i].name << " ";
	}

}

//Courses section
void Course_Creation() {// <================ Creates new course file and puts it in a new struct

	Course Courses;
	Courses.id = 0;
	Courses.number_of_enrolled = 0;
	string file = "Course";
	string ext = ".txt";


	for (int ID = 0; ID < 20; ID++) {

		string filename = file + to_string(ID) + ext;
		ifstream Course_File("Courses_file/" + filename);

		if (Course_File) {

			Course_File.close();
			Courses.id++;
			continue;
		}
		else {


			SetConsoleTextAttribute(h, 6);
			cout << "\n\t\t\t __                   __               \n";
			cout << "\t\t\t/   __ _  _ _|_ _    /   _     __ _  _ \n";
			cout << "\t\t\t\\__ | (/_(_| |_(/_   \\__(_)|_| | _> (/_\n";


			SetConsoleTextAttribute(h, 3);
			string FileName = file + to_string(ID) + ext;
			ofstream courses("Courses_file/" + FileName);

			cout << "\t\t\tEnter name of course : ";

			SetConsoleTextAttribute(h, 15);
			cin >> Courses.name;

			for (int i = 0; i < 20; i++) {

				if (Courses.id_of_student_enrolled[i] == -1) {

					continue;
				}
				else {
					Courses.number_of_enrolled++;
				}
			}
			courses << Courses.id << " " << Courses.name << " " << Courses.number_of_enrolled << " ";
			for (int i = 0; i < 20; i++) {
				if (Courses.id_of_student_enrolled[i] == -1) {
					continue;
				}
				else {
					courses << Courses.id_of_student_enrolled[i] << " ";
				}
			}
			courses << endl;
			courses.close();
			break;
		}
	}
}

int  Course_Display() {// <============== Displays all Courses in the system and takes the an id of course to display more info for this course



	{SetConsoleTextAttribute(h, 6);
	cout << "\n\t\t\t __                              \n";
	cout << "\t\t\t/   _     __ _  _     |  o  _ _|_\n";
	cout << "\t\t\t\\__(_)|_| | _> (/_    |  | _>  |_\n";


	}

	int r[20];
	for (int ID = 0; ID < 20; ID++) {

		string File_name = "Course" + to_string(ID) + ".txt";
		fstream File;

		File.open("Courses_file/" + File_name);
		for (int i = 0; i < 20; i++)
		{

			r[i] = Courses[i].id;
		}

		if (File) {

			File >> Courses[ID].id >> Courses[ID].name >> Courses[ID].number_of_enrolled >> Courses[ID].id_of_student_enrolled[0] >> Courses[ID].id_of_student_enrolled[1] >> Courses[ID].id_of_student_enrolled[2] >> Courses[ID].id_of_student_enrolled[3] >> Courses[ID].id_of_student_enrolled[4] >> Courses[ID].id_of_student_enrolled[5] >> Courses[ID].id_of_student_enrolled[6] >> Courses[ID].id_of_student_enrolled[7] >> Courses[ID].id_of_student_enrolled[8] >> Courses[ID].id_of_student_enrolled[9];
			if (Courses[ID].name.size() > 2) {

				SetConsoleTextAttribute(h, 3);
				cout << "\t\t\t\t\t\t\t\tID of Course: ";

				SetConsoleTextAttribute(h, 8);
				cout << Courses[ID].id;



				SetConsoleTextAttribute(h, 3);
				cout << "\t\t  ||   Name of Course: ";

				SetConsoleTextAttribute(h, 8);
				cout << Courses[ID].name;


				SetConsoleTextAttribute(h, 6);
				cout << "\n\n\t\t\t\t\t\t\t\t______________________________________________________";
			}
			for (int i = 0; i < 10; i++)
			{
				if (Courses[ID].id_of_student_enrolled[i] != -1) {

					Courses[ID].students_names[i] = (Students[Courses[ID].id_of_student_enrolled[i]].username);


				}
			}cout << "\n\n";





		}




	}

	cout << "\t\t\t\t\t\t\t\tSelect The Course ID For More Options :";
	SetConsoleTextAttribute(h, 15);
	cin >> j;

	system("CLS");

	SetConsoleTextAttribute(h, 3);
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\tID of Course: ";

	SetConsoleTextAttribute(h, 8);
	cout << Courses[j].id;


	SetConsoleTextAttribute(h, 3);
	cout << "       Name of Course: ";

	SetConsoleTextAttribute(h, 8);
	cout << Courses[j].name;

	if (Find_Item(r,10,j))
	{



		for (int i = 0; i < 10; i++)
		{
			if (Courses[j].id_of_student_enrolled[i] != -1) {



				Courses[j].students_names[i] = (Students[Courses[j].id_of_student_enrolled[i]].username);
				if (Courses[j].students_names[i].size() > 3) {

					SetConsoleTextAttribute(h, 6);
					cout << "\n\n\t\t\t\t\t\t\t\t\t\t___________________________________________________________\n";

					cout << "\t\t\t\t\t\t\t\t\t\t||   ID: ";

					SetConsoleTextAttribute(h, 3);
					cout << Courses[j].id_of_student_enrolled[i];

					SetConsoleTextAttribute(h, 6);
					cout << "\t\tName: ";

					SetConsoleTextAttribute(h, 3);
					cout << Courses[j].students_names[i] << " ";

					SetConsoleTextAttribute(h, 6);
					cout << "\t\tMark: ";

					SetConsoleTextAttribute(h, 3);
					cout << marks[j][i] << "||\n";
				}
			}

		}
	}

	else {
		SetConsoleTextAttribute(h, 4);
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tIt does not exist" << endl;
	}
	return j;
}

void Add_course(int student_id, int course_id) { // <================ Adds the ID of the course to the courses enrolled in the Student file & Adds the ID of Student that enrolled in the Course in the course File
	int stud_id = student_id;
	int cour_id = course_id;


	string filename;
	filename = "Course" + to_string(cour_id) + ".txt";
	ofstream file("Courses_file/" + filename, ios_base::app);
	file << " " << to_string(stud_id);



	filename = "Student" + to_string(stud_id) + ".txt";

	ofstream sfile("Students_file/" + filename, ios_base::app);

	sfile << " " << to_string(cour_id);

	Fetch_Data();



}

void Display_All_Students() {
	int ID;
	Fetch_Data();
	int arr[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	SetConsoleTextAttribute(h, 14);
	{cout << "\t\t\t\t\t\t\t\t __                                 \n";
	cout << "\t\t\t\t\t\t\t\t(_ _|_    _| _ __ _|_   |   o  _ _|_\n";
	cout << "\t\t\t\t\t\t\t\t__) |_|_|(_|(/_| | |_   |__ | _>  |_\n\n"; }
	for (ID = 0; ID < 10; ID++)
	{
		string file = "Student" + to_string(ID) + ".txt";
		fstream w("Students_file/" + file);
		
		arr[ID] = Students[ID].Id;
		int c = 0;

		if (!w)
		{
			break;
		}
		else
		{
			w >> Students[ID].Id >> Students[ID].username >> Students[ID].password >> Students[ID].number_of_courses_enrolled >> Students[ID].Courses_enrolled[0].id >> Students[ID].Courses_enrolled[1].id >> Students[ID].Courses_enrolled[2].id >> Students[ID].Courses_enrolled[3].id >> Students[ID].Courses_enrolled[4].id >> Students[ID].Courses_enrolled[5].id >> Students[ID].Courses_enrolled[6].id >> Students[ID].Courses_enrolled[7].id >> Students[ID].Courses_enrolled[8].id >> Students[ID].Courses_enrolled[8].id >> Students[ID].Courses_enrolled[9].id;

			SetConsoleTextAttribute(h, 11);
			cout << "\t\t\t\t\t\t\t\t| Student ID | " << "\t" << "| Student name |" << "\t" << "Student password: " << "\t" << "number of courses enrolled: \n"; SetConsoleTextAttribute(h, 8);
			cout << "\t\t\t\t\t\t\t\t    | " << Students[ID].Id << " |" << "\t" << "    |" << Students[ID].username << " |" << "\t" << "\t  | " << Students[ID].password << " |" << "\t" << "\t         | " << Students[ID].number_of_courses_enrolled << " |" << endl << endl; SetConsoleTextAttribute(h, 6);
			
			cout << "\t\t\t\t\t\t\t\t" << "______________________________________________________________________________________";


		}
		string a = "Student" + to_string(ID + 1) + ".txt";
		fstream g("Students_file/" + a);
		if (g)
			cout << endl;
	}
	int x;
	cout << "\n\n\t\t\t\t\t\t\t\t Select A Student for More info: ";
	bool found = false;

	int i = 0;
	bool notfound = true;
	while (notfound) {
		SetConsoleTextAttribute(h, 15);
		cin >> x;
		//verifies the input
		notfound = true;
		for (size_t i = 0; i < 10; i++)
		{
			if (arr[i] == x)
			{
				notfound = false;
				break;
			}


		}
		if (x >= 0 && x <= 10) {
			if (notfound)
			{
				SetConsoleTextAttribute(h, 4);
				cout << "\n\n\t\t\t\t\t\t\t\t Invalid ID: ";
			}
		}
	}
	system("CLS");
	Fetch_Data();

	SetConsoleTextAttribute(h, 6);
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\tStudent ID: ";

	SetConsoleTextAttribute(h, 3);
	cout << Students[x].Id;

	SetConsoleTextAttribute(h, 6);
	cout << "     Student name: ";
	SetConsoleTextAttribute(h, 3);

	cout << Students[x].username << "\n";
	for (int i = 0; i < Students[x].number_of_courses_enrolled; i++)
	{
		cout << "\n\n\t\t\t\t\t\t\t\tCourse " << i + 1 << ":  Course ID :";
		SetConsoleTextAttribute(h, 8);
		cout << Students[x].Courses_enrolled[i].id; cout << "                  Course Name: ";

		SetConsoleTextAttribute(h, 3); SetConsoleTextAttribute(h, 8);
		cout << Courses[Students[x].Courses_enrolled[i].id].name;

		SetConsoleTextAttribute(h, 3);
		cout << "    Mark: ";

		SetConsoleTextAttribute(h, 8);

		cout << marks[x][Students[x].Courses_enrolled[i].id] << endl;

		SetConsoleTextAttribute(h, 14);
		cout << "\n\t\t\t\t\t\t\t\t\t_______________________________________________________________________________"; SetConsoleTextAttribute(h, 3);
	}
	{SetConsoleTextAttribute(h, 14);
	cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tEdit Student: \n\t\t\t\t\t\t\t\t\t\t\t___________________\n"; SetConsoleTextAttribute(h, 3);
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t1-Edit Student's Name\n";
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t2-Edit Student's Marks\n";
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t0-Exit\n";}

	int choice;
	cout << "\n\n\t\t\t\t\t\t\t\t\t\tPlease enter your choice: "; 
	
	
	bool right = true;
	while (right) 
	{	
		SetConsoleTextAttribute(h, 15);
		cin >> choice;
	
			switch (choice)
			{
			case 1: {Student_Edit(x);right = false; break; }
			case 2: {Edit_Marks(x);right = false; break; }
			case 0: { right = false;break; }

			default: {SetConsoleTextAttribute(h, 4);	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tInvalid Input:  ";cin.ignore();cin.clear(); break;}
			}
		
		
	}
}

void Admin_Menu() {// <=============== has all the functions in one place for the Admin to choose what he wants 
	system("CLS");
	int choice; SetConsoleTextAttribute(h, 3);
	cout << "\n\n\t\t\t    _        _           _             ___           _     _                   \n";
	cout << "\t\t\t   /_\\    __| |  _ __   (_)  _ _      / _ \\   _ __  | |_  (_)  ___   _ _    ___\n";
	cout << "\t\t\t  / _ \\  / _` | | '  \\  | | | ' \\    | (_) | | '_ \\ |  _| | | / _ \\ | ' \\  (_-<\n";
	cout << "\t\t\t /_/ \\_\\ \\__,_| |_|_|_| |_| |_||_|    \\___/  | .__/  \\__| |_| \\___/ |_||_| /__/\n";
	cout << "\t\t\t                                             |_|                               \n";

	SetConsoleTextAttribute(h, 6);
	cout << "\t\t____________________________________________________________________________________________\n\n";
	SetConsoleTextAttribute(h, 14);

	cout << "\t\t\t1- Create A New Student\n\n";
	cout << "\t\t\t2- Display All Students\n\n";
	cout << "\t\t\t3- Create A New Course\n\n";
	cout << "\t\t\t4- Display All Courses\n\t\t\t____________________\n\n";
	cout << "\t\t\t5- View More Info about the Project \n\n";
	cout << "\t\t\t0- To Exit\n\n";

	SetConsoleTextAttribute(h, 6);
	cout << "\n\n\n\n\n\n\n\t\t\tPlease Enter Your Choice: ";

	SetConsoleTextAttribute(h, 15);
	cin >> choice;

	switch (choice)
	{
	case 1: {system("CLS"); Student_Creation(); system("pause"); ; break; }
	case 2: {system("CLS"); Display_All_Students(); system("pause"); break; }
	case 3: {system("CLS"); Course_Creation(); system("pause"); break; }
	case 4: {system("CLS");	Course_Display(); system("pause"); break; }
	case 5: {program_details(); break; }
	case 0: {admin_loop = false;	break;  break; }
	default:
		break;
	}
}

void Student_Menu(int x) { // <==================== has all the functions for the Student to do
	int stud_id = x;
	system("CLS");
	{SetConsoleTextAttribute(h, 6);

	cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t  " << Students[stud_id].username << "'s Account";
	cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t______________________\n\n\n";

	SetConsoleTextAttribute(h, 3);

	cout << "\t\t\t\t\t\t\t\t\t\t\t\tOptions:\n\t\t\t\t\t\t\t\t\t\t\t\t----------------\n\n\n";
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t1- Enroll In New Course\n\n\t\t\t\t\t\t\t\t\t\t\t\t2- View Your info\n\t\t\t\t\t\t\t\t\t\t\t\t_______________________\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t3- View more Info about the Project \n\n\t\t\t\t\t\t\t\t\t\t\t\t0- Exit \n\n\t\t\t\t\t\t\t\t\t\t\t Enter Choice: ";

	int y;
	
	bool right = true;
	while (right) {SetConsoleTextAttribute(h, 15);
			cin >> y;
		switch (y)
		{
			
		case 1: {Add_course(stud_id, Student_Enroll(stud_id)); system("pause"); right = false; break; }
		case 2: {Student_Info(stud_id); system("pause");right = false; break; }
		case 3: {program_details();break;}
		case 0: {student_loop = false;right = false; break; }

		default: {SetConsoleTextAttribute(h, 4);cout <<  "\n\n\t\t\t\t\t\t\t\t\t\t\t\t Invalid Choice: ";
			break;}
		}
	}
	}
}

int main()
{
	bool run_program = true;
	while (run_program) {
		system("CLS");
		Fetch_Data();
		system("CLS");
		Fetch_marks();

		//entering admin gate
		admin_loop = true;
		student_loop = true;

		int id_of_stud = Entry_Check(Admin_Or_User());
		if (id_of_stud == -1)
		{
			while (admin_loop) {
				Admin_Menu();




			}

		}//entering Student gate
		else {
			while (student_loop) {
				Student_Menu(id_of_stud);

			}
		}

	}
	Fetch_marks();
}