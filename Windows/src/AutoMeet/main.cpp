#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>


using namespace std;

int button_menu(string text, int number_of_choices, string choices[]);
void time_line_menu();
void all_meetings_menu();
void add_new_meeting_menu();
void resave_data();
void select_and_modify_menu();
void help();
void settings();
void initialize_settings();
void set_theme(int choice);

struct meeting {
    string name;
    string link;
    int number_of_days_in_week;
    int days_of_the_week[7];
    int hour;
    int minut;
};


int is_before(meeting meet1, meeting meet2) {
    /* returns 1 if meet1 be before meet2 */
    if (meet1.hour < meet2.hour || (meet1.hour == meet2.hour && meet1.minut <= meet2.minut)) {
        return 1;
    }
    return 0;
}

int get_number_of_day(const char* day_in_letters){
    char first_char = *day_in_letters;
    char second_char = *(day_in_letters+1);
    switch (first_char) {
    case 'S':
        if (second_char == 'u'){
            return 1;
        }
        if (second_char == 'a') {
            return 0;
        }
        break;
    case 'M':
        return 2;
        break;
    case 'T':
        if (second_char == 'u'){
            return 3;
        }
        if (second_char == 'h') {
            return 6;
        }
        break;
    case 'W':
        return 5;
    case 'F':
        return 7;
    default:
        return -1;
    }
    return -1;

}

meeting all_meetings[31];
int number_of_meetings = 0;
int exists_test() {
    if (FILE *file = fopen("C:/ProgramData/TeymooriAnar/AutoMeet/ListOfMeetings.txt", "r")) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
}
int exists_test_of_settings() {
    if (FILE *file = fopen("C:/ProgramData/TeymooriAnar/AutoMeet/Settings.txt", "r")) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
}
void initialize_settings() {
    int exist = exists_test_of_settings();
    if (exist == 0) {
        system("mkdir \"C:/ProgramData/TeymooriAnar/AutoMeet/\"");
        ofstream data_file("C:/ProgramData/TeymooriAnar/AutoMeet/Settings.txt");
        data_file << "0";
        data_file.close();
    }

    string text_of_file = "";
    ifstream data_file("C:/ProgramData/TeymooriAnar/AutoMeet/Settings.txt");
    getline(data_file, text_of_file);
    int number_of_theme;
    //stringstream number_of_theme_str;
    stringstream number_of_theme_str(text_of_file);
    number_of_theme_str >> number_of_theme;
    set_theme(number_of_theme);


}
void initialize_all_meetings() {
    int exist = exists_test();
    if (exist == 0) {
        system("mkdir \"C:/ProgramData/TeymooriAnar/AutoMeet/\"");
        ofstream data_file("C:/ProgramData/TeymooriAnar/AutoMeet/ListOfMeetings.txt");
        data_file << "";
        data_file.close();
    }

    string text_of_file;
    int number_of_meeting_to_save = 0;
    int number_of_days;
    stringstream number_of_days_str;
    int day;
    ifstream data_file("C:/ProgramData/TeymooriAnar/AutoMeet/ListOfMeetings.txt");
    while (getline(data_file, text_of_file)) {
         // Output the text from the file
        meeting meet;
        meet.name = text_of_file;
        getline(data_file, text_of_file);
        meet.link = text_of_file;
        getline(data_file, text_of_file);
        stringstream number_of_days_str(text_of_file);
        number_of_days_str >> number_of_days;
        meet.number_of_days_in_week = number_of_days;
        while (number_of_days > 0) {
            getline(data_file, text_of_file);
            stringstream number_of_days_str(text_of_file);
            number_of_days_str >> day;
            meet.days_of_the_week[meet.number_of_days_in_week-number_of_days] = day;
            number_of_days --;
        }
        getline(data_file, text_of_file);
        stringstream number_of_hour_str(text_of_file);
        number_of_hour_str >> day;
        meet.hour = day;

        getline(data_file, text_of_file);
        stringstream number_of_min_str(text_of_file);
        number_of_min_str >> day;
        meet.minut = day;
        all_meetings[number_of_meetings] = meet;
        number_of_meetings ++;

    }
    // // Close the file
     data_file.close();
}

int is_for_today(meeting meet, int today_int) {
    for (int i=0; i<meet.number_of_days_in_week; i++) {
        if (meet.days_of_the_week[i] == today_int) {
            return 1;
        }
    }
    return 0;
}

int main() {
    initialize_all_meetings();
    initialize_settings();

    string choices[] = {"TIME LINE",
                 "ALL MEETINGS",
                 "NEW MEETING",
                 "STOP BACKGROUND SERVICE",
                 "START/RESTART",
                 "SETTINGS",
                 "HELP"};

    while(1) {
        system("cls");
        int choice = button_menu("Hello! Welcome to AutoMeet app by Mahdi Teymoori Anar!\n\nMENU:\n\n",
                    7,
                    choices);
        switch (choice) {
            case 1:
                time_line_menu();
                break;
            case 2:
                all_meetings_menu();
                break;
            case 3:
                add_new_meeting_menu();
                break;
            case 4:
                system("taskkill /im AutoMeet(BackgroundService).exe");
                break;
            case 5:
                system("taskkill /im AutoMeet(BackgroundService).exe");
                system("start AutoMeet(BackgroundService).exe");
                break;
            case 6:
                settings();
                break;
            case 7:
                help();
                break;
        }
    }
}

void set_theme(int choice) {
    int all_colors = 17;
    choice = (choice % all_colors) + 1;
    switch (choice) {
    case 1:
        system("color 07");
        break;
    case 2:
        system("color 70");
        break;
    case 3:
        system("color 87");
        break;
    case 4:
        system("color 78");
        break;
    case 5:
        system("color 24");
        break;
    case 6:
        system("color 42");
        break;
    case 7:
        system("color 82");
        break;
    case 8:
        system("color 28");
        break;
    case 9:
        system("color 34");
        break;
    case 10:
        system("color 43");
        break;
    case 11:
        system("color 35");
        break;
    case 12:
        system("color 53");
        break;
    case 13:
        system("color 5c");
        break;
    case 14:
        system("color 31");
        break;
    case 15:
        system("color 13");
        break;
    case 16:
        system("color 1a");
        break;
    case 17:
        system("color a1");
        break;
    }
    ofstream data_file("C:/ProgramData/TeymooriAnar/AutoMeet/Settings.txt");
    data_file << "" << (choice-1);
    data_file.close();
}

void theme_select() {
    int color_to_set;
    cout << "enter an integer" << endl;
    fflush(stdin);
    scanf("%d", &color_to_set);
    set_theme(color_to_set);
    return;
}

void settings() {
    string choices[] = {"THEME", "BACK"};
    while (1) {
        system("cls");
        int choice = button_menu("========SETTINGS========",
                    2,
                    choices);
        if (choice == 2) {
            break;
        } else {
            theme_select();
        }
    }
    return;
}

void help() {
    cout << "Here you can see what each choice does:" << endl;
    cout << "____________________" << endl;
    cout << "TIME LINE : view a list of opcoming meetings for today." << endl;
    cout << "____________________" << endl;
    cout << "ALL MEETINGS : view a list of all meetings of the week and change and modify them." << endl;
    cout << "____________________" << endl;
    cout << "NEW MEETING : add a new meeting." << endl;
    cout << "____________________" << endl;
    cout << "STOP BACKGROUND SERVICE : stops background service until next time you set up your computer, or select button START" << endl;
    cout << "____________________" << endl;
    cout << "START/RESTART : starts/restarts background service" << endl;
    cout << "____________________" << endl;
    cout << "TIME LINE : view a list of opcomig meetings for today." << endl;
    cout << "____________________" << endl;
    cout << "SETTINGS : some settings and customizations" << endl;
    cout << "____________________" << endl;
    cout << "\n\npress ENTER to go back" << endl;
    fflush(stdin);
    scanf("%*c");
    return;
}

int button_menu(string text, int number_of_choices, string choices[]) {
    cout << text << endl;
    for (int i = 0; i < number_of_choices; i++)
    {
        cout << (i+1) << ") " << choices[i] << endl;
    }
    int choice;
    string choice_string;
    do {
        cout << "input a number : ";
        cin >> choice_string;
        stringstream choice_parser(choice_string);
        choice_parser >> choice;
        if (choice > number_of_choices || choice <= 0)
        {
            cout << "You should enter an integer between 1 and " << number_of_choices << ".\nTry again!\n" <<endl;
        }

    } while (choice <= 0 || choice > number_of_choices);
    system("cls");
    return choice;
}

void all_meetings_menu() {
    for (int i = 0; i < number_of_meetings; i++) {
        cout << "name : " << all_meetings[i].name << "\nlink : " << all_meetings[i].link << "\n" << all_meetings[i].number_of_days_in_week
                << (all_meetings[i].number_of_days_in_week == 1 ? " day in the week on day \n" : " days in the week on days \n");
        for (int j = 0; j < all_meetings[i].number_of_days_in_week; j++)
        {
            cout << all_meetings[i].days_of_the_week[j] << (j != all_meetings[i].number_of_days_in_week-1 ? ", " : "\n");
        }
        cout << "at time " << all_meetings[i].hour << ":" << all_meetings[i].minut << "\n_______________________________________" << endl;

    }
    string choices[] = {"ADD A MEETING\tadd a meeting",
                "SELECT A MEETING\tselect a meeting to modify or delete",
                "GO BACK\tgo back to the main menu"};
    int button_choice = button_menu("\n\n", 3, choices);
    switch (button_choice){
        case 1:
            add_new_meeting_menu();
            break;
        case 2:
            select_and_modify_menu();
            break;
        case 3:
            return;
        default:
            break;
    }
}

void time_line_menu() {
    time_t now;
    char* dt;
    int today_number;
    meeting meet;
    int opened;
    int is_any_upcoming;
    int next_meet_set = 0;
    meeting next_meet;
    int to_wait;
    // current date/time based on current system
    now = time(0);
    opened = 0;
    // convert now to string form
    dt = ctime(&now);
    tm *ltm = localtime(&now);
    today_number = get_number_of_day(dt);
    is_any_upcoming = 0;
    for (int i = 0; i < number_of_meetings; i++) {
        meet = all_meetings[i];
        if (is_for_today(meet, today_number) == 1) {

            if (meet.hour > ltm->tm_hour || (meet.hour == ltm->tm_hour && meet.minut > ltm->tm_min)){
                cout << "There is an upcoming meeting for today : " << meet.name << "\tat time\t" << meet.hour << ":" << meet.minut << endl;
                if(next_meet_set == 0) {
                    next_meet = meet;
                    next_meet_set = 1;
                } else {
                    if (is_before(meet, next_meet)) {
                        next_meet = meet;
                    }
                }
                is_any_upcoming = 1;
            }
            if ((ltm->tm_hour == meet.hour && ltm->tm_min <= meet.minut && ltm->tm_min >= meet.minut - 30)||(ltm->tm_hour == meet.hour - 1 && ltm->tm_min-30>=meet.minut)) {
                string command = "start "+meet.link;
                const char * command_char_ptr = command.c_str();
                cout << "Opening meeting "<<meet.name<<" for time "<<meet.hour<<":"<<meet.minut<<" ... "<<endl;
                system(command_char_ptr);
                opened = 1;
            }
        }

    }
    if (is_any_upcoming == 0) {
        cout << "There is not any upcoming event for today! GoodLuck!" << endl;
    }
    cout << "\n\n\nPress ENTER to go back!" << endl;
    fflush(stdin);
    getchar();
    system("cls");
    return;

}

void add_new_meeting_menu() {
    meeting new_meet;
    system("cls");
    cout << "NEW MEETING" << endl;
    if (number_of_meetings >= 30) {
        cout << "You can at most have 30 meetings.\nEach meeting can be repeated at most 7 days a week." << endl;
        cout << "Delete at least meeting to be able to add new meetings;)" << endl;
        return;
    }
    cout << "To cancel, just close the application window!" << endl;
    cout << "\n\nStep1 : Select a name for the meeting.\n\nname : ";
    fflush(stdin);
    getline(cin, new_meet.name);
    system("cls");
    fflush(stdin);
    cout << "NEW MEETING|" << new_meet.name << endl;
    cout << "To cancel, just close the application window!" << endl;
    cout << "\n\nStep2 : Enter the link of meeting to open when the meeting starts\n\nlink : ";
    cin >> new_meet.link;
    system("cls");
    fflush(stdin);
    cout << "NEW MEETING|" << new_meet.name << endl;
    cout << "To cancel, just close the application window!" << endl;
    cout << "\n\nStep3 : Enter the number of meeting's days in the week\n\nnumber of days in a week : ";
    string number_of_days_string;
    cin >> number_of_days_string;
    stringstream number_Of_days_int(number_of_days_string);
    number_Of_days_int >> new_meet.number_of_days_in_week;
    system("cls");
    fflush(stdin);
    cout << "NEW MEETING|" << new_meet.name << endl;
    cout << "To cancel, just close the application window!" << endl;
    cout << "\n\nStep4 : Enter the meeting's days in the week line by line\n0 Means Saturday/Shanbe, ..., and 7 means Friday/Jom'e\n\nnumber of day in a week : " << endl;
    for (int i = 0; i < new_meet.number_of_days_in_week; i++)
    {

        fflush(stdin);
        cin >> number_of_days_string;
        stringstream number_Of_days_int(number_of_days_string);
        number_Of_days_int >> new_meet.days_of_the_week[i];
    }

    system("cls");
    fflush(stdin);
    cout << "NEW MEETING|" << new_meet.name << endl;
    cout << "To cancel, just close the application window!" << endl;
    cout << "\n\nStep5 : Enter the meeting's time\n\nhour : ";

    cin >> number_of_days_string;
    stringstream hour_int(number_of_days_string);
    hour_int >> new_meet.hour;
    cout << "minut : ";
    fflush(stdin);
    cin >> number_of_days_string;
    stringstream minut_int(number_of_days_string);
        minut_int >> new_meet.minut;

    all_meetings[number_of_meetings] = new_meet;
    number_of_meetings ++;

    resave_data();


}

void resave_data() {
    string text_of_file_to_save = "";
    int number;
    string str;
    for (int i = 0; i < number_of_meetings; i++)
    {
        stringstream ss;
        ss << all_meetings[i].number_of_days_in_week;
        ss >> str;
        text_of_file_to_save += all_meetings[i].name+"\n"+all_meetings[i].link+"\n"+str+"\n";
        for (int j = 0; j < all_meetings[i].number_of_days_in_week; j++)
        {
            stringstream ssday;
            ssday << all_meetings[i].days_of_the_week[j];
            ssday >> str;
            text_of_file_to_save += str+"\n";
        }

        stringstream sshour;
        sshour << all_meetings[i].hour;
        sshour >> str;
        text_of_file_to_save += str+"\n";
        stringstream ssmin;
        ssmin << all_meetings[i].minut;
        ssmin >> str;
        text_of_file_to_save += str;
        if (i < number_of_meetings - 1)
        {
            text_of_file_to_save += "\n";
        }

    }

    ofstream data_file("C:/ProgramData/TeymooriAnar/AutoMeet/ListOfMeetings.txt");
    data_file << text_of_file_to_save;
    data_file.close();
    system("taskkill /im AutoMeet(BackgroundService).exe");
    system("start AutoMeet(BackgroundService).exe");

}

void select_and_modify_menu() {
    system("cls");
    string names[20];
    for (int i = 0; i < number_of_meetings; i++)
    {
        names[i] = all_meetings[i].name;
    }
    int choice = button_menu("Here is a list of names of all meetings. Decide one of them :\n", number_of_meetings, names);
    choice--;
    system("cls");
    cout << all_meetings[choice].name << endl;
    string options[] = {"OPEN NOW",
                        "CHANGE NAME",
                        "CHANGE LINK",
                        "CHANGE HOUR",
                        "CHANGE MINUT",
                        "DELETE",
                        "CANCEL"};
    int choice2 = button_menu("What do you want to do?", 7, options);
    if (choice2 == 1) {
        string command = "start "+all_meetings[choice].link;
                const char * command_char_ptr = command.c_str();
                cout << "Opening meeting "<<all_meetings[choice].name<<" ... "<<endl;
                system(command_char_ptr);
    } else if (choice2 == 2)
    {
        fflush(stdin);
        cout << "new name : ";
        string new_name;
        getline(cin, new_name);
        all_meetings[choice].name = new_name;
    } else if (choice2 == 3) {
        fflush(stdin);
        cout << "new link : ";
        string new_link;
        getline(cin, new_link);
        all_meetings[choice].link = new_link;

    } else if (choice2 == 4) {
        fflush(stdin);
        cout << "new hour : ";
        string new_hour_string;
        getline(cin, new_hour_string);
        stringstream ss(new_hour_string);
        int new_hour_int;
        ss >> new_hour_int;
        all_meetings[choice].hour = new_hour_int;
    } else if (choice2 == 5) {
        fflush(stdin);
        cout << "new minut : ";
        string new_hour_string;
        getline(cin, new_hour_string);
        stringstream ss(new_hour_string);
        int new_hour_int;
        ss >> new_hour_int;
        all_meetings[choice].hour = new_hour_int;
    } else if (choice2 == 6) {
        for (int i = choice; i < number_of_meetings-1; i++)
        {
            all_meetings[i] = all_meetings[i+1];
        }
        number_of_meetings--;
    } else if (choice2 == 7) {
        return;
    }

    resave_data();
    return;
}
