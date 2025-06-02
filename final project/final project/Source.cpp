//code simulates a basic hotel management system allowing users to
// book rooms,cancel bookings, display room status, and search for guest
#include <iostream>
using namespace std;

string name_save[10][3];//2D array to store names of guests booked in rooms

class Node //Class representing a room in the hostel
{
public:
    int room_capacity = 1; //maximum capacity of the room
    int fill_room = 0;//number of guests in the room
    char name[3][10];//array to store guest names
    // Pointers to the next and previous nodes 
    Node* next;
    Node* previous;
};

class hotel
{
    Node* head[3];
    Node* created_node;
public:
    hotel()
    {
        for (int i = 0; i < 3; i++)
            head[i] = NULL;//initialize head pointers to NULL
    }
    void create();//method to initialize or create rooms for the hostel
    void book(int);//to book a room for guest
    void cancel(int);//to cancel a room
    void display();//to display the current status of rooms
    void search(string);//to search for a guest's name


};
//create a room
void hotel::create()
{
    //looping through floors
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)//looping through rooms on each floor
        {
            Node* newnode = new Node;
            newnode->next = NULL;
            newnode->previous = NULL;
            if (head[i] == NULL)
            {
                head[i] = newnode;
                //set initial room capacity
                newnode->room_capacity = 1;
            }
            else
            {
                Node* created_node = head[i];
                //while loop to repeat the menu until the user decides to exit
                while (created_node->next != NULL)
                {
                    created_node = created_node->next;
                }
                if (j == 3 || j == 5 || j == 7 || j == 8)// Adjust room capacities based on room number
                {
                    created_node->room_capacity = 3;
                }
                if (j == 2 || j == 4 || j == 6)
                {
                    created_node->room_capacity = 2;
                }
                created_node->next = newnode;
                newnode->previous = created_node;
            }
        }
    }
}
//book room for guest
void hotel::book(int people)
{
    int floor, room;
    cout << "Enter the floor number: ";
    cin >> floor;
    //check if entered floor number is less than 0 or greater than 4
    if (floor < 0 || floor > 4)
    {
        cout << "Invalid floor number : " << floor << endl;
    }
    else
    {
        //Set the pointer to point to the appropriate node
        created_node = head[floor - 1];
        cout << "Enter the room number: ";
        cin >> room;
        //check if the entered room number is less than 0 or greater than 10
        if (room < 0 || room > 10)
        {
            cout << "Invalid room number: " << room << endl;
        }
        else
        {
            int i = 1;
            while (i < room)
            {
                created_node = created_node->next;
                i++;
            }
            //Check if room capacity is greater than or equal to requested number of people
            if (created_node->room_capacity >= people)
            {
                cout << "Room is Available! You can BOOK the Room!" << endl;
                int count = 0;
                while (created_node->fill_room - 1 <= created_node->room_capacity)
                {
                    cout << "Enter Name: " << created_node->fill_room + 1 << ": ";
                    cin >> created_node->name[created_node->fill_room];
                    cout << "Re-Enter Name - " << created_node->fill_room + 1 << ": ";
                    cin >> name_save[room - 1][floor - 1];
                    count++;
                    created_node->fill_room++;
                    if (count >= people)
                    {
                        break;
                    }
                }
                //decrease the room capacity by the number of people booked
                created_node->room_capacity = created_node->room_capacity - people;
            }
            else
            {
                cout << "Room of your choice is currently not Available" << endl;
            }
        }
    }
}
// cancel room
void hotel::cancel(int check)
{
    char namecheck[10];
    int flag = 0;
    int room, i = 1;
    //checks if entered floor number is less than 0 or greater than 4
    if (check < 0 || check > 4)
    {
        cout << "Invalid Floor No.: " << check << endl;
    }
    else
    {
        cout << "Enter Room Number: ";
        cin >> room;
        if (room < 0 || room > 10)
        {
            cout << "Invalid Room number: " << room << endl;
        }
        else
        {
            cout << "Enter the name to be deleted: ";
            cin >> namecheck;
            string ncheck = namecheck;
            search(ncheck);
            created_node = head[check - 1];
            while (i < room)
            {
                created_node = created_node->next;//advances the created_node pointer to the next node
                i++;
            }
            i = 0;
            while (i < 3)
            {
                //compare string stored in namecheck with the name stored in created_node
                if (!strcmp(namecheck, created_node->name[i]))
                {
                    flag = 1;
                    break;
                    i = 0;
                }
                else
                    i++;
            }
            //check if flag is set to 1 and if the room is not empty 
            if (flag == 1 && created_node->fill_room != 0)
            {
                cout << "Record deleted : " << created_node->name[i] << endl;
                created_node->name[i][0] = 'A';//replace first character of the i-th name with letter ‘A’.
                created_node->name[i][1] = '\0';
                created_node->fill_room--;
                created_node->room_capacity++;
            }
            else
                cout << "\nRecord Not Avaiable" << endl;
        }
    }
}
//display hotel rooms and vacancies
void hotel::display()
{
    int j = 0, k = 0, l = 0;
    for (int i = 0; i < 60; i++)
    {
        cout << "**";
    }
    cout << endl;
    //floor label
    for (int i = 1; i < 4; i++)
    {
        cout << "\tFLOOR : " << i << "\t\t";
    }
    cout << endl;
    for (int i = 0; i < 60; i++)
    {
        cout << "**";
    }
    //initialize pointers to linked list nodes
    created_node = head[j];
    Node* secondfloor_node = head[j + 1];
    Node* thirdfloor_node = head[j + 2];
    cout << endl;
    //display room info
    while (created_node != NULL)
    {
        //Check room availability 
        if (created_node->fill_room != created_node->room_capacity && created_node->room_capacity != 0)
        {
            j++;
            cout << " Room " << j << "|";
            cout << "Vacant Room for: " << created_node->room_capacity;
        }
        else
        {
            j++;
            cout << "| Room " << j << "|";
            cout << " Already Booked by: " << name_save[j - 1][0];
        }
        if (secondfloor_node->fill_room != secondfloor_node->room_capacity && secondfloor_node->room_capacity != 0)
        {
            k++;
            cout << "\t| Room " << k << "|";
            cout << "Vacant Room for: " << secondfloor_node->room_capacity;
        }
        else
        {
            k++;
            cout << "\t| Room " << k << "|";
            cout << "\t Already Booked by: " << name_save[k - 1][1];
        }
        if (thirdfloor_node->fill_room != thirdfloor_node->room_capacity && thirdfloor_node->room_capacity != 0)
        {
            l++;
            cout << "\t| Room " << l << "|";
            cout << "Vacant Room for: " << thirdfloor_node->room_capacity << "| ";
        }
        else
        {
            l++;
            cout << "| Room " << l << "|";
            cout << "\t Already Booked by: " << name_save[l - 1][2];
        }
        cout << "" << endl;
        cout << endl;
        created_node = created_node->next;
        secondfloor_node = secondfloor_node->next;
        thirdfloor_node = thirdfloor_node->next;
    }
    for (int i = 0; i < 60; i++)
    {
        cout << "**";
    }
    cout << endl;
}
//function to search a guest by name
void hotel::search(string key)
{
    bool found = 0;
    int i_position;
    int j_position;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (name_save[i][j] == key)
            {
                found = 1;
                i_position = i;
                j_position = j;
                break;
            }
        }
    }
    if (found)
    {
        cout << "Name Found at \nRoom no " << i_position + 1 << "\nFloor no. " << j_position + 1 << endl;
    }
    else
    {
        cout << "Name not found " << endl;
    }
}
//main menu
int main()
{
    hotel management;
    int choice, floorcheck;
    char ch;
    string namecheck;
    management.create();// method to create rooms, including looping through floors and adjusting room capacities.
    do
    {
        cout << "\t\t\t \t_HOTEL MANAGEMENT SYSTEM_" << endl;
        cout << "\t\t\t\t1) Display Current Status of Rooms" << endl;
        cout << "\t\t\t\t2) Book a Room for 1 person" << endl;
        cout << "\t\t\t\t3) Book a Room for 2 person" << endl;
        cout << "\t\t\t\t4) Book a Room for 3 person" << endl;
        cout << "\t\t\t\t5) Cancel a Room" << endl;
        cout << "\t\t\t\t6) Search a Name" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;
        //switch case to choose menu option
        switch (choice)
        {
        case 1:
            management.display();//displaying room status, including iterating through floors and displaying room information
            break;
        case 2:
            management.book(1);// booking rooms, checking availability, and updating room capacities.
            break;
        case 3:
            management.book(2);
            break;
        case 4:
            management.book(3);
            break;
        case 5:
            cout << "Enter Floor no.: ";
            cin >> floorcheck;
            management.cancel(floorcheck);//canceling room bookings, including searching for the guest's name and updating room capacities.
            break;
        case 6:
            cout << "Enter name: ";
            cin >> namecheck;
            management.search(namecheck);//searching for guests by name, including looping through the name array.
            break;
        default:
            cout << "Invalid Choice" << endl;
        }
        //option to continue or exit 
        cout << "Do You want to Continue (Y/N): ";
        cin >> ch;
        cout << endl;
    } while (ch == 'Y' || ch == 'y');
    return 0;
}