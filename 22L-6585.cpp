#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class SocialNetwork;
class User;
class Page;
class Comment;
class Post;
class Activity;
class Date;
class Object;
class Memory;

class Helper
{
public:
	static int StringLength(char*& str)
	{
		int length = 0;

		for (length; str[length] != '\0'; length++)
		{

		}

		return length;
	}
	static char* GetStringFromBuffer(char*& src)
	{
		int length = StringLength(src);
		char* dest = new char[length + 1];

		for (int index = 0; index < length; index++)
		{
			dest[index] = src[index];
		}
		dest[length] = '\0';

		return dest;
	}
	static bool CheckString(char* str, char str2[])
	{
		bool found = true;
		int length1 = StringLength(str);
		int length2 = StringLength(str2);

		if (length1 != length2)
		{
			found = false;
		}
		else
		{
			for (int index = 0; index < length1; index++)
			{
				if (str[index] != str2[index])
				{
					found = false;
					break;
				}
			}
		}

		return found;
	}
	static char* ConvertNumtoString(int number)
	{
		int length = log10(number) + 1;
		char* temp = new char[length + 1];
		int power , digit;
		
		for (int i = 0; i < length; i++)
		{
			power = pow(10, length - i - 1);
			digit = (number / power) % 10;
			temp[i] = digit + 48;
		}
		temp[length] = '\0';
		return temp;
	}
	static char* Concatenate(char str1[], char*& str2)
	{
		int length1 = StringLength(str1);
		int length2 = StringLength(str2);
		int total = length1 + length2;
		int i = 0;

		char* temp = new char[total + 1];

		for (int index = 0; index < length1; index++)
		{
			temp[index] = str1[index];
		}
		for (int index = length1; index < total; index++)
		{
			temp[index] = str2[i];
			i++;
		}
		temp[total] = '\0';

		return temp;
	}
};

class Object
{
private:
	char* ID;
public:
	Object()
	{
		ID = 0;
	}
	virtual Object* SearchByID()
	{
		return 0;
	}
	virtual void Print()
	{

	}
	void SetID(char* id)
	{
		ID = Helper::GetStringFromBuffer(id);
	}
	char* GetID()
	{
		return ID;
	}
	virtual void SetTimeline(Post* post)
	{

	}
	void PrintID()
	{
		cout << ID << "--";
	}
	~Object()
	{
		if (ID != 0)
		{
			delete[] ID;
			ID = 0;
		}
	}
};

class Activity
{
private:
	int type;
	char* value;
	char* text;
public:
	void SetActivity(char t , char* message)
	{
		type = t - 48;
		char* ptr = 0;

		if (t == '1')
		{
			char temp[] = "Feeling";
			ptr = temp;
			value = Helper::GetStringFromBuffer(ptr);
		}
		else if (t == '2')
		{
			char temp[] = "Thinking About";
			ptr = temp;
			value = Helper::GetStringFromBuffer(ptr);
		}
		else if (t == '3')
		{
			char temp[] = "Making";
			ptr = temp;
			value = Helper::GetStringFromBuffer(ptr);
		}
		else if (t == '4')
		{
			char temp[] = "Celebrating";
			ptr = temp;
			value = Helper::GetStringFromBuffer(ptr);
		}

		text = Helper::GetStringFromBuffer(message);
	}
	void Print()
	{
		cout << value << " " << text << endl;
	}
	~Activity()
	{
		if (text != 0)
		{
			delete[] text;
		}
		if (value != 0)
		{
			delete[] value;
		}
	}
};

class Date
{
private:
	int day;
	int month;
	int year;
public:
	static Date Today;
	Date()
	{
		day = 1;
		month = 1;
		year = 2020;
	}
	Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	void Print()
	{
		cout << "(" << day << "/" << month << "/" << year << ")" << endl;
	}
	void SetDate(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	bool PreviousDate(Date& date)
	{
		bool previous = false;
		if (date.day == (day-1)  && date.month == month && date.year == year)
		{
			previous = true;
		}
		return previous;
	}
	bool EqualDate(Date& date)
	{
		bool equal = false;
		if (date.day == day && date.month == month && date.year == year)
		{
			equal = true;
		}
		return equal;
	}
	int TimeElapsedinYears(Date& date)
	{
		int elapsed = 0;
		if (day == date.day && month == date.month && year > date.year)
		{
			elapsed = year - date.year;
		}
		return elapsed;
	}
};

class Page : public Object
{
private:
	char* name;
	Post** timeline;
	int totalposts;
	static int totalPages;
public:
	Page()
	{
		name = 0;
		timeline = 0;
		totalposts = 0;
	}
	void ReadDataFromFile(ifstream& readFile)
	{
		char* temp = new char[100];
		readFile >> temp;
		readFile.ignore();
		Object::SetID(temp);
		readFile.getline(temp, 100);
		name = Helper::GetStringFromBuffer(temp);
		delete[] temp;
		temp = 0;
	}
	void Print()
	{
		cout << name << " ";
	}
	static void SetTotalPages(int number)
	{
		totalPages = number;
	}
	static int GetTotalPages()
	{
		return totalPages;
	}
	Page* SearchByID(char id[])
	{
		if (Helper::CheckString(Object::GetID(), id) == true)
		{
			return this;
		}
		else
		{
			return 0;
		}
	}
	void SetTimeline(Post*);
	void ViewTimeline();
	void ViewLatestPosts(Date&);
	~Page();
};

class User : public Object
{
private:
	char* first_name;
	char* last_name;
	int totalFriends;
	int totalLikedPages;
	int totalposts;
	User** friendsList;
	Page** likedPages;
	Post** timeline;
	static int totalUsers;
public:
	User()
	{
		first_name = 0;
		last_name = 0;
		friendsList = 0;
		likedPages = 0;
		totalFriends = 0;
		totalLikedPages = 0;
		totalposts = 0;
		timeline = 0;
	}
	void ReadDataFromFile(ifstream& readFile)
	{
		char* temp = new char[100];
		readFile >> temp;
		Object::SetID(temp);
		readFile >> temp;
		first_name = Helper::GetStringFromBuffer(temp);
		readFile >> temp;
		last_name = Helper::GetStringFromBuffer(temp);

		delete[] temp;
		temp = 0;
	}
	void Print()
	{
		cout << first_name << " " << last_name << " ";
	}
	void PrintFriendList()
	{
		cout << first_name << " " << last_name << " -- Friend List" << endl << endl;
		if (friendsList == 0)
		{
			cout << "No Friends" << endl;
		}
		else
		{
			for (int index = 0; index < totalFriends ; index++)
			{
				friendsList[index]->PrintID();
				friendsList[index]->Print();
				cout << endl;
			}
			cout << endl << endl;
		}
	}
	void PrintLikedPagesList()
	{
		cout << first_name << " " << last_name << " -- Liked Pages" << endl << endl;
		if (likedPages == 0)
		{
			cout << "No Liked Pages" << endl;
		}
		else
		{
			for (int index = 0; index < totalLikedPages; index++)
			{
				likedPages[index]->PrintID();
				likedPages[index]->Print();
				cout << endl;
			}
			cout << endl << endl;
		}
	}
	void AddFriend(User*& user)
	{
		if (friendsList == 0)
		{
			friendsList = new User * [10];
		}	
		bool found = false;
		for (int i = 0; i < totalFriends; i++)
		{
			if (user == friendsList[i])
			{
				found = true;
				break;
			}
		}
		if (found == false && totalFriends < 10)
		{
			friendsList[totalFriends] = user;
			totalFriends++;
		}
	}
	void AddLikedPage(Page*& page)
	{
		if (likedPages == 0)
		{
			likedPages = new Page* [10];
		}
		bool found = false;
		for (int i = 0; i < totalLikedPages; i++)
		{
			if (page == likedPages[i])
			{
				found = true;
				break;
			}
		}
		if (found == false && totalLikedPages < 10)
		{
			likedPages[totalLikedPages] = page;
			totalLikedPages++;
		}	
	}
	bool IsaFriend(char* UserID)
	{
		bool isA = false;
		for (int index = 0; index < totalFriends; index++)
		{
			if (Helper::CheckString(friendsList[index]->GetID(), UserID) == true)
			{
				isA = true;
				break;
			}
		}
		return isA;
	}
	bool IsaLikedPage(char* PageID)
	{
		bool likedpage = false;
		for (int index = 0; index < totalLikedPages; index++)
		{
			if (Helper::CheckString(likedPages[index]->GetID(), PageID) == true)
			{
				likedpage = true;
			}
		}
		return likedpage;
	}
	static void SetTotalUsers(int number)
	{
		totalUsers = number;
	}
	static int GetTotalUsers()
	{
		return totalUsers;
	}
	User* SearchByID(char id[])
	{
		if (Helper::CheckString(Object::GetID(), id) == true)
		{
			return this;
		}
		else
		{
			return 0;
		}
	}
	void SetTimeline(Post*);
	void ViewTimeline();
	void ViewHome()
	{
		cout << first_name << " " << last_name << " - Home Page" << endl << endl;
		for (int index = 0; index < totalFriends; index++)
		{
			friendsList[index]->ViewLatestPosts(Date::Today);
		}
		for (int index = 0; index < totalLikedPages; index++)
		{
			likedPages[index]->ViewLatestPosts(Date::Today);
		}
	}
	void ViewLatestPosts(Date&);
	int GetTotalPosts()
	{
		return totalposts;
	}
	Post* GetTimeline(int number)
	{
		return timeline[number];
	}
	void SeeMemories();
	~User();
};

class Post
{
protected:
	char* ID;
	char* text;
	int numberofLikes;
	Object* SharedBy;
	Object** WhoLiked;
	Activity* activity;
	Comment** comments;
	Date date;
	int totalcomments;
	bool IsaMemory;
	static int totalPosts;
public:
	Post()
	{
		ID = 0;
		text = 0;
		numberofLikes = 0;
		WhoLiked = 0;
		activity = 0;
		comments = 0;
		SharedBy = 0;
		totalcomments = 0;
		IsaMemory = false;
	}
	Post(char* id, char* t, Object* Shared , bool memory)
	{
		ID = Helper::GetStringFromBuffer(id);
		text = Helper::GetStringFromBuffer(t);
		numberofLikes = 0;
		if (Shared->GetID()[0] == 'u')
		{
			SharedBy = new User;
			SharedBy = Shared;
		}
		else
		{
			SharedBy = new Page;
			SharedBy = Shared;
		}
		WhoLiked = 0;
		activity = 0;
		comments = 0;
		totalcomments = 0;
		date = Date::Today;
		IsaMemory = memory;
	}
	void ReadDataFromFile(ifstream& readFile)
	{
		char postType;
		char* temp = new char[60];
		char type;
		int d, m, y;

		readFile >> postType;
		readFile >> temp;

		ID = Helper::GetStringFromBuffer(temp);

		readFile >> d;
		readFile >> m;
		readFile >> y;
		date.SetDate(d, m, y);

		readFile.ignore();
		readFile.getline(temp, 100);
		text = Helper::GetStringFromBuffer(temp);

		if (postType == '2')
		{
			readFile >> type;
			readFile.getline(temp, 100);
			activity = new Activity;
			activity->SetActivity(type, temp);
		}
		else
		{
			activity = 0;
		}

		temp = 0;
		delete[] temp;
	}
	void SetSharedBy(Object*& obj)
	{
		SharedBy = obj;
	}
	void SetWhoLiked(Object*& obj)
	{
		if (WhoLiked == 0)
		{
			WhoLiked = new Object * [10];
		}
		WhoLiked[numberofLikes] = obj;
		numberofLikes++;
	}
	void SetRemainingWhoLiked()
	{
		if (WhoLiked == 0)
		{
			WhoLiked = new Object * [10];
		}
		for (int index = numberofLikes; index < 10; index++)
		{
			WhoLiked[index] = 0;
		}
	}
	static void SetTotalPosts(int p)
	{
		totalPosts = p;
	}
	void PrintWhoLiked()
	{
		if (WhoLiked == 0)
		{
			cout << "This Post is liked by no one" << endl;
		}
		else
		{
			cout << "Post Liked By: " << endl;
			for (int index = 0; index < numberofLikes; index++)
			{
				if (WhoLiked[index] == 0)
				{
					break;
				}
				else
				{
					WhoLiked[index]->PrintID();
					WhoLiked[index]->Print();
					cout << endl;
				}
			}
		}
	}
	static int GetTotalPosts()
	{
		return totalPosts;
	}
	char* GetID()
	{
		return ID;
	}
	virtual void ViewPost(bool, bool);
	int GetLikes()
	{
		return numberofLikes;
	}
	bool GetIsaMemory()
	{
		return IsaMemory;
	}
	 void SetLikes()
	{
		 if (numberofLikes < 10)
		 {
			 numberofLikes++;
		 }
	}
	bool CheckIfAlreadyLiked(char id[])
	{
		bool found = false;
		char* temp;

		for (int index = 0; index < numberofLikes; index++)
		{
			temp = WhoLiked[index]->GetID();
			if (Helper::CheckString(temp, id) == true)
			{
				found = true;
				break;
			}
		}

		return found;
	}
	bool CheckLikeLimit()
	{
		if (numberofLikes >= 10)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	Object* GetSharedBy()
	{
		return SharedBy;
	}
	Post* SearchByID(char id[])
	{
		if (Helper::CheckString(ID, id) == true)
		{
			return this;
		}
		else
		{
			return 0;
		}
	}
	Date& GetDate()
	{
		return date;
	}
	void AddComment(Comment*& com)
	{
		if (comments == 0)
		{
			comments = new Comment* [10];
		}
		if (totalcomments < 10)
		{
			comments[totalcomments] = com;
			totalcomments++;
		}
	}
	~Post()
	{
		if (ID != 0)
		{
			delete ID;
			ID = 0;
		}
		if (text != 0)
		{
			delete text;
			text = 0;
		}
		if (activity != 0)
		{
			delete activity;
			activity = 0;
		}
		if (comments != 0)
		{
			delete comments;
			comments = 0;
		}

	}
};

class Comment
{
private:
	char* ID;
	Post* whichPost;
	Object* byWho;
	char* text;
	static int totalComments;
public:
	Comment()
	{
		ID = 0;
		whichPost = 0;
		byWho = 0;
		text = 0;
	}
	Comment(char* id, Post*& post, Object* who, char* t)
	{
		ID = id;
		whichPost = post;
		byWho = who;
		text = Helper::GetStringFromBuffer(t);
	}
	void SetValues(char* id, Post*& post, Object*& obj, char* t)
	{
		ID = Helper::GetStringFromBuffer(id);
		whichPost = post;
		byWho = obj;
		text = Helper::GetStringFromBuffer(t);
	}
	static void SetTotalComments(int t)
	{
		totalComments = t;
	}
	static int GetTotalComments()
	{
		return totalComments;
	}
	void Print()
	{
		cout << "\t";
		byWho->Print();
		cout << "wrote: " << text << endl;
	}
	Object* GetByWho()
	{
		return byWho;
	}
	Post* GetWhichPost()
	{
		return whichPost;
	}
	~Comment()
	{
		if (ID != 0)
		{
			delete[] ID;
			ID = 0;
		}
		if (text != 0)
		{
			delete[] text;
			text = 0;
		}
	}
};

class Memory : public Post
{
private:
	Post* oldPost;
public:
	Memory()
	{
		oldPost = 0;
	}
	Memory(char* id ,char* t, Post*& old)
	{
		oldPost = old;
		ID = id;
		text = Helper::GetStringFromBuffer(t);
		WhoLiked = 0;
		SharedBy = oldPost->GetSharedBy();
		activity = 0;
		comments = 0;
		totalcomments = 0;
		date = Date::Today;
		IsaMemory = true;
		numberofLikes = 0;
	}
	static bool CheckifMemory(Post*& post)
	{
		Date date1;
		bool is = false;

		date1 = post->GetDate();
		if (Date::Today.TimeElapsedinYears(date1) != 0)
		{
			is = true;
		}
		return is;
	}
	void ViewPost(bool d , bool m)
	{
		Post::ViewPost(true, false);
		cout << "\t";
		oldPost->ViewPost(true, true);
	}
	~Memory()
	{
	}
};

Date Date::Today(15, 11, 2017);

class SocialNetwork
{
private:
	User** Users;
	Page** Pages;
	Post** Posts;
	User* currentUser;
public:
	void LoadPagesFromFile()
	{
		ifstream readFile;
		readFile.open("Pages.txt");
		int totalPages;
		char* temp = new char[100];

		readFile >> totalPages;
		Pages = new Page * [totalPages];
		Page::SetTotalPages(totalPages);

		for (int index = 0; index < totalPages; index++)
		{
			Pages[index] = new Page;
			Pages[index]->ReadDataFromFile(readFile);
		}

		readFile.close();
	}
	void LoadUsersFromFile()
	{
		ifstream readFile;
		readFile.open("Users.txt");
		int totalUsers;
		int index = 0 , count = 0 , length;
		char* temp = new char[100];
		bool stop = false;
		char temp2[] = "-1";
		int totalPages = Page::GetTotalPages();
		char*** tempFriendList = 0;

		readFile >> totalUsers;
		readFile.ignore();
		Users = new User * [totalUsers];
		User::SetTotalUsers(totalUsers);
		tempFriendList = new char** [totalUsers];

		while (!readFile.eof())
		{
			stop = false;
			count = 0;
			Users[index] = new User;
			Users[index]->ReadDataFromFile(readFile);
			tempFriendList[index] = new char* [10];
			do
			{
				readFile >> temp;
				if (Helper::CheckString(temp, temp2) == true)
				{
					length = Helper::StringLength(temp);
					tempFriendList[index][count] = new char[length + 1];
					for (int i = 0; i < length; i++)
					{
						tempFriendList[index][count][i] = temp[i];
					}
					tempFriendList[index][count][length] = '\0';
					stop = true;
				}
				else
				{
					length = Helper::StringLength(temp);
					tempFriendList[index][count] = new char[length + 1];
					for (int i = 0; i < length; i++)
					{
						tempFriendList[index][count][i] = temp[i];
					}
					tempFriendList[index][count][length] = '\0';
					count++;
				}
			} while (stop == false);
			
			for (count; count < 10; count++)
			{
				tempFriendList[index][count] = 0;
			}

			stop = false;

			do
			{
				readFile >> temp;
				if (Helper::CheckString(temp, temp2) == true)
				{
					stop = true;
				}
				else
				{
					for (int i = 0; i < totalPages; i++)
					{
						if (Helper::CheckString(temp, Pages[i]->GetID()) == true)
						{
							Users[index]->AddLikedPage(Pages[i]);
							break;
						}
					}
				}
			} while (stop == false);
			index++;
		}

		readFile.close();

		for (int i = 0; i < totalUsers; i++)
		{			
			for (int j = 0; j < totalUsers; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					if (tempFriendList[i][k] == 0)
					{
						break;
					}
					else if (Helper::CheckString(Users[j]->GetID(), tempFriendList[i][k]) == true)
					{
						Users[i]->AddFriend(Users[j]);
						break;
					}

				}
			}
		}
	}
	void LoadPostsFromFile()
	{
		ifstream readFile;
		readFile.open("Posts.txt");
		int totalPosts;
		char* temp = new char[50];

		readFile >> totalPosts;
		Post::SetTotalPosts(totalPosts);
		Posts = new Post * [totalPosts];
		Object* Shared;
		Object* WhoLiked;

		for (int index = 0; index < totalPosts; index++)
		{
			Posts[index] = new Post;
			Posts[index]->ReadDataFromFile(readFile);

			readFile >> temp;
			if (temp[0] == 'u')
			{
				Shared = new User;
				Shared = SearchUserbyID(temp);
				Posts[index]->SetSharedBy(Shared);
			}
			else
			{
				Shared = new Page;
				Shared = SearchPagebyID(temp);
				Posts[index]->SetSharedBy(Shared);
			}

			readFile >> temp;
			while (temp[0] != '-')
			{
				if (temp[0] == 'u')
				{
					WhoLiked = new User;
					WhoLiked = SearchUserbyID(temp);
					Posts[index]->SetWhoLiked(WhoLiked);
				}
				else
				{
					WhoLiked = new Page;
					WhoLiked = SearchPagebyID(temp);
					Posts[index]->SetWhoLiked(WhoLiked);
				}
				readFile >> temp;
			}

			Posts[index]->SetRemainingWhoLiked();
			Shared->SetTimeline(Posts[index]);
		}

		readFile.close();
		delete[] temp;
	}
	void LoadCommentsFromFile()
	{
		ifstream readFile;
		int total;
		readFile.open("Comments.txt");

		readFile >> total;
		Comment::SetTotalComments(total);
		char* temp1 = new char[100];
		char* temp2 = new char[100];
		char* temp3 = new char[100];
		char* temp4 = new char[100];
		Post* post;
		Object* obj;

		for (int index = 0; index < total; index++)
		{
			Comment* Comments = new Comment;
			readFile >> temp1;

			readFile >> temp2;
			post = SearchPostbyID(temp2);
			
			readFile >> temp3;
			if (temp3[0] == 'u')
			{
				obj = new User;
				obj = SearchUserbyID(temp3);
			}
			else
			{
				obj = new Page;
				obj = SearchPagebyID(temp3);
			}

			readFile.ignore();
			readFile.getline(temp4, 100);
			Comments->SetValues(temp1, post, obj, temp4);
			post->AddComment(Comments);
		}
		
		readFile.close();
	}
	void Load()
	{
		LoadPagesFromFile();
		LoadUsersFromFile();
		LoadPostsFromFile();
		LoadCommentsFromFile();
	}
	void UpdatePosts(Post* newpost)
	{
		Post** newlist = new Post * [Post::GetTotalPosts() + 1];
		for (int index = 0; index < Post::GetTotalPosts(); index++)
		{
			if (Posts[index]->GetIsaMemory() == true)
			{
				newlist[index] = new Memory;
			}
			else
			{
				newlist[index] = new Post;
			}
			newlist[index] = Posts[index];
		}

		delete[] Posts;

		if (newpost->GetIsaMemory() == true)
		{
			newlist[Post::GetTotalPosts()] = new Memory;
		}
		else
		{
			newlist[Post::GetTotalPosts()] = new Post;
		}
		newlist[Post::GetTotalPosts()] = newpost;
		Posts = newlist;
		newlist = 0;
		Post::SetTotalPosts(Post::GetTotalPosts() + 1);
	}
	User* SearchUserbyID(char UserID[])
	{
		int totalUsers = User::GetTotalUsers();
		bool found;
		User* SearchUser = 0;

		for (int index = 0; index < totalUsers; index++)
		{
			found = Helper::CheckString(Users[index]->GetID(), UserID);
			if (found == true)
			{
				SearchUser = Users[index];
				break;
			}
		}

		return SearchUser;
	}
	Page* SearchPagebyID(char PageID[])
	{
		int totalPages =  Page::GetTotalPages();
		bool found;
		Page* SearchPage = 0;

		for (int index = 0; index < totalPages; index++)
		{
			found = Helper::CheckString(Pages[index]->GetID(), PageID);
			if (found == true)
			{
				SearchPage = Pages[index];
				break;
			}
		}

		return SearchPage;
	}
	Post* SearchPostbyID(char PostID[])
	{
		char* temp = new char[10];

		for (int index = 0; index < Post::GetTotalPosts(); index++)
		{
			temp = Posts[index]->GetID();
			if (Helper::CheckString(temp, PostID) == true)
			{
				return Posts[index];
			}
		}
		delete[] temp;
		return 0;
	}
	void PrintPostLikedList(char PostID[])
	{
		char* ID; 

		for (int index = 0; index < Post::GetTotalPosts(); index++)
		{
			ID = Posts[index]->GetID();
			if (Helper::CheckString(ID, PostID))
			{
				Posts[index]->PrintWhoLiked();
				break;
			}
		}
	}
	void ViewPostByID(char PostID[])
	{
		int totalPosts = Post::GetTotalPosts();
		Post* which = 0;

		for (int index = 0; index < totalPosts; index++)
		{
			char* temp = Posts[index]->GetID();
			if (Helper::CheckString(temp, PostID) == true)
			{
				Posts[index]->ViewPost(true , Posts[index]->GetIsaMemory());
				break;
			}
		}
	}
	void LikeaPost(char PostID[], char ID[])
	{
		char* temp;
		int number;
		bool already , doable;
		int total;
		Object* who;

		for (int index = 0; index < Post::GetTotalPosts(); index++)
		{
			temp = Posts[index]->GetID();
			if (Helper::CheckString(temp, PostID) == true)
			{
				already = Posts[index]->CheckIfAlreadyLiked(ID);
				doable = Posts[index]->CheckLikeLimit();
				if (already == false && doable == true)
				{
					total = Posts[index]->GetLikes();
					if (ID[0] == 'u')
					{
						who = new User;
						who = SearchUserbyID(ID);
						Posts[index]->SetWhoLiked(who);
					}
					else
					{
						who = new Page;
						who = SearchPagebyID(ID);
						Posts[index]->SetWhoLiked(who);
					}
				}
				break;
			}
		}
	}
	void ViewPageByID(char PageID[])
	{
		Page* currentPage = SearchPagebyID(PageID);
		currentPage->ViewTimeline();
		currentPage = 0;
	}
	User* GetCurrentUser()
	{
		return currentUser;
	}
	void AddComment(char postID[], char text[])
	{
		Post* post = new Post;
		post = SearchPostbyID(postID);
		char str1[] = "c";
		char* str2 = Helper::ConvertNumtoString(Comment::GetTotalComments() + 1);
		char* temp = Helper::Concatenate(str1, str2);
		Object* who = new User;
		who = GetCurrentUser();

		Comment* newcomment = new Comment(temp, post, who, text);
		post->AddComment(newcomment);
	}
	void SeeYourMemories()
	{
		currentUser->SeeMemories();
	}
	void ShareMemory(char PostID[], char* text)
	{
		bool IsMemory;
		Post* post;

		post = SearchPostbyID(PostID);
		if (Helper::CheckString(currentUser->GetID(), post->GetSharedBy()->GetID()) == true)
		{
			IsMemory = Memory::CheckifMemory(post);
			if (IsMemory == true)
			{
				char str1[] = "post";
				char* str2 = Helper::ConvertNumtoString(Post::GetTotalPosts() + 1);
				char* id = Helper::Concatenate(str1, str2);
				Memory* newMemory = new Memory(id, text, post);
				currentUser->SetTimeline(newMemory);
				UpdatePosts(newMemory);
			}
		}

	}
	void Run()
	{
		cout << "Command: Set Current System Date 15 11 2017" << endl;
		cout << "System Date:\t";
		Date::Today.Print();
		cout << endl << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		Load();
		char ID[] = "u7";
		currentUser = SearchUserbyID(ID);

		if (currentUser != 0)
		{
			cout << "Command: Set Current User " << ID << endl;
			currentUser->Print();
			cout << " successfully set as Current User" << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			cout << "Command: View Friend List" << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			currentUser->PrintFriendList();
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			cout << "Command: View Liked Pages" << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			currentUser->PrintLikedPagesList();
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			cout << "Command: View Home " << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			currentUser->ViewHome();
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			cout << "Command: View Timeline " << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			currentUser->ViewTimeline();
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			char postID[] = "post5";
			cout << "Command: View LikedList " << postID << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			PrintPostLikedList(postID);
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			cout << "Command:: Like a Post " << postID << " by " << ID << endl;
			LikeaPost(postID, ID);
			cout << "------------------------------------------------------------------------------------------------" << endl;
			cout << "Command: View LikedList " << postID << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			PrintPostLikedList(postID);
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			cout << "Command: View Post " << postID << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			ViewPostByID(postID);
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

			char postID2[] = "post4";
			char text[] = "Good Luck For your Result";
			cout << "Command: Post Comment " << endl;
			AddComment(postID2, text);
			cout << "Command: View Post " << postID2 << endl;
			ViewPostByID(postID2);
			cout << "------------------------------------------------------------------------------------------------" << endl;


			char postID3[] = "post8";
			char text2[] = "Thanks for the wishes";
			cout << "Command: Post Comment " << endl;
			AddComment(postID3, text2);
			cout << "Command: View Post " << postID3 << endl;
			ViewPostByID(postID3);
			cout << "------------------------------------------------------------------------------------------------" << endl;


			cout << "Command: SeeYourMemories()" << endl << endl;
			SeeYourMemories();
			cout << "------------------------------------------------------------------------------------------------" << endl;

			char postID4[] = "post10";
			char text3[] = "Never thought I will be a specialist in this field...";
			cout << "Command: ShareMemory" << endl;
			ShareMemory(postID4, text3);
			cout << "------------------------------------------------------------------------------------------------" << endl;
			cout << "Command: View Timeline" << endl;
			currentUser->ViewTimeline();
			cout << "------------------------------------------------------------------------------------------------" << endl;

			char pageID[] = "p1";

			cout << "Command: View Page " << pageID << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;
			ViewPageByID(pageID);
			cout << endl << endl;
			cout << "------------------------------------------------------------------------------------------------" << endl;

		}
		else
		{
			cout << "No such User exist" << endl;
		}

		char ID2[] = "u11";
		currentUser = SearchUserbyID(ID2);

		if (currentUser != 0)
		{

			cout << "Command: View Home " << endl;
			currentUser->ViewHome();
			cout << "------------------------------------------------------------------------------------------------" << endl;

			cout << "Command: View Timeline" << endl;
			currentUser->ViewTimeline();
			cout << "------------------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			cout << "No such User exist" << endl;
		}
	}
	~SocialNetwork()
	{
		for (int index = 0; index < User::GetTotalUsers(); index++)
		{
			if (Users[index] != 0)
			{
				delete Users[index];
				Users[index] = 0;
			}
		}
		if (Users != 0)
		{
			delete Users;
		}

		for (int index = 0; index < Page::GetTotalPages(); index++)
		{
			if (Pages[index] != 0)
			{
				delete Pages[index];
				Pages[index] = 0;
			}
		}
		if (Pages != 0)
		{
			delete Pages;
		}

		if (Posts != 0)
		{
			delete[] Posts;
		}
	}
};

int User::totalUsers = 0;
int Page::totalPages = 0;
int Post::totalPosts = 0;
int Comment::totalComments = 0;

void Post::ViewPost(bool d , bool m)
{
	{
		cout << "---";
		if (activity == 0)
		{
			SharedBy->Print();
			cout << "shared " << text;
			cout << "   ";
			if (d == true)
			{
				date.Print();
			}
			cout << endl;
		}
		else
		{
			SharedBy->Print();
			cout << "is ";
			activity->Print();
			cout << text << "   ";
			if (d == true)
			{
				date.Print();
			}
			cout << endl;
		}

		if (m == false)
		{
			for (int index = 0; index < totalcomments; index++)
			{
				comments[index]->Print();
			}
		}
	}
}
void User::ViewTimeline()
{
	cout << first_name << " " << last_name << " - Timeline" << endl << endl;
	for (int index = 0; index < totalposts; index++)
	{
		timeline[index]->ViewPost(true , timeline[index]->GetIsaMemory());
		cout << endl;
	}
}
void Page::ViewTimeline()
{
	cout << name << " - Timeline" << endl << endl;
	for (int index = 0; index < totalposts; index++)
	{
		timeline[index]->ViewPost(true, timeline[index]->GetIsaMemory());
		cout << endl;
	}
}
void User::ViewLatestPosts(Date& date)
{
	Date date2;
	for (int index = 0; index < totalposts; index++)
	{
		date2 = timeline[index]->GetDate();
		if (date.EqualDate(date2) == true || date.PreviousDate(date2) == true)
		{
			timeline[index]->ViewPost(false, timeline[index]->GetIsaMemory());
			cout << endl;
		}
	}
}
void Page::ViewLatestPosts(Date& date)
{
	Date date2;
	for (int index = 0; index < totalposts; index++)
	{
		date2 = timeline[index]->GetDate();
		if (date.EqualDate(date2) == true || date.PreviousDate(date2) == true)
		{
			timeline[index]->ViewPost(false , timeline[index]->GetIsaMemory());
			cout << endl;
		}
	}
}
void User::SeeMemories()
{
	Date date1;

	cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago." << endl << endl;

	for (int index = 0; index < totalposts; index++)
	{
		date1 = timeline[index]->GetDate();
		if (Date::Today.TimeElapsedinYears(date1) != 0)
		{
			cout << "On this Day" << endl;
			cout << Date::Today.TimeElapsedinYears(date1) << " Years Ago " << endl;
			timeline[index]->ViewPost(true, true);
		}
	}
}
User::~User()
{
	if (first_name != 0)
	{
		delete first_name;
		first_name = 0;
	}
	if (last_name != 0)
	{
		delete last_name;
		last_name = 0;
	}
	if (friendsList != 0)
	{
		delete[] friendsList;
		friendsList = 0;
	}
	if (likedPages != 0)
	{
		delete[] likedPages;
		likedPages = 0;
	}
	if (timeline != 0)
	{
		delete timeline;
		timeline = 0;
	}
}
Page::~Page()
{
	if (name != 0)
	{
		delete name;
		name = 0;
	}
	if (timeline != 0)
	{
		delete timeline;
		timeline = 0;
	}
}
void User::SetTimeline(Post* post)
{
	if (timeline == 0)
	{
		timeline = new Post * [10];
	}
	if (totalposts < 10)
	{
		timeline[totalposts] = post;
		totalposts++;
	}
}
void Page::SetTimeline(Post* post)
{
	if (timeline == 0)
	{
		timeline = new Post * [10];
	}
	if (totalposts < 10)
	{
		timeline[totalposts] = post;
		totalposts++;
	}
}

int main()
{
	SocialNetwork FaceBook;
	FaceBook.Run();
	system("pause");
	return 0;
}