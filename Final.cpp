#include <iostream>
#include <fstream>

using namespace std;

class Facebook;
class User;
class Page;
class Helper;
class Post;
class Date;
class Object;
class Activity;
class Comment;
class Memory;
class Helper
{
public:
	static int strlen(char* finder)
	{
		int i=0;
		while (finder[i]!='\0')
		{
			i++;
		}
		return i;
	}
	static void strcpy(char* dest , char *src)
	{
		int i=0;
		while (src[i]!='\0')
		{
			dest[i]=src[i];
			i++;
		}
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(char* temp)
	{
		int length = strlen(temp);
		char* result = new char [length+1];
		strcpy(result , temp);
		return result;
	}
	static int strcmp(char* str1, char* str2)
	{
		int i = 0;
		while (str1[i] != '\0' || str2[i] != '\0')
		{
			if (str1[i] != str2[i])
			{
				return 1;
			}
			i++;
		}
		return 0;
	}
	static char* StringConcatenate(char arr1[], char arr2[]) {
		int i, j,m=0;
		int L1 = strlen(arr1);
		int L2 = strlen(arr2);
		char*arr3 = new char[L1+L2+2];
		for (i = 0; arr1[i] != '\0'; i++) {
			arr3[i] = arr1[i];
		}
		arr3[i]='\n';
		i+=1;
		for (j=i ; arr2[m]!='\0';j++)
		{
			arr3[j]=arr2[m];
			m++;
		}
		arr3[L1+L2+2] = '\0';
		return arr3;

	}
};

class Date
{
private:
	int day;
	int month;
	int year;
public:
	static Date CurrentDate;
	Date()
	{
		day=1;
		month=1;
		year=1990;
	}
	void ReadDateFromFile(ifstream&fin)
	{
		fin>>day;
		fin>>month;
		fin>>year;
	}
	void PrintDate()
	{
		cout<<"("<<day<<"/"<<month<<"/"<<year<<")";
	}
	static void SetCurrentDate(int d , int m , int y)
	{
		CurrentDate.day=d;
		CurrentDate.month=m;
		CurrentDate.year=y;
	}
	int CompareDate(Date compare)
	{
		if (compare.day-1==this->day&&compare.day==this->day+1)
		{
			return 1;
		}
		else
			return 0;
	}
	int CompareMemory(Date check)
	{
		if (check.day==this->day&&check.month==this->month&&check.year>this->year)
		{
			return 1;
		}
		else
			return 0;
	}
	int GetYear()
	{
		return year;
	}
	~Date()
	{
	}
};
Date Date::CurrentDate = Date();
class Object
{
private:
	char*ID;
public:
	Object()
	{
		ID="";
	}
	~Object()
	{
		if (ID!="")
		{
			delete ID;
		}
	}
	virtual void PostOnFeed(Post*){}
	virtual void ViewUser(){};
};

class Activity
{
private :
	int type;
	char*value;
public:
	Activity()
	{
		type=1;
		value="Excited";
	}
	void ReadActivityFromFile(ifstream&fin)
	{
		fin>>type;
		char buf[80];
		fin.getline(buf , 80);
		value = Helper::GetStringFromBuffer(buf);
	}
	void PrintActivity()
	{
		if (type==1)
		{
			cout<<" is Feeling "<<value;
		}
		if (type==2)
		{
			cout<<" is Thinking about "<<value;
		}
		if (type==3)
		{
			cout<<" is Making "<<value;
		}
		if (type==4)
		{
			cout<<" is Celebrating "<<value;
		}
	}
	~Activity()
	{
		if (value)
			delete value;
	}
};

class Comment
{
private :
	char*C_ID;
	char*text;
	Object* comment;
public:
	Comment()
	{
		C_ID="";
		text="";
		comment=0;
	}
	void SetComment(char*id , char*Text , Object*CommentBy)
	{
		C_ID = Helper::GetStringFromBuffer(id);
		text = Helper::GetStringFromBuffer(Text);
		comment = CommentBy;
	}
	void PrintComment()
	{
		comment->ViewUser();
		cout<<" wrote : ";
		cout<<"\t";
		cout<<text;
		cout<<endl;
	}
	~Comment()
	{
		if(C_ID)
		{
			delete C_ID;
			C_ID="";
		}
		if (text)
		{
			delete text;
			text ="";
		}
	}
};

class Post
{
private :
	int type;
	char*ID;
	char*text;
	Date SharedDate;
	Activity* activity;
	Object*postedBy;
	Object**LikedByAddress;
	Comment**comments;
	int numOfLikes;
	int numOfComments;
public:
	Post()
	{
		type=1;
		text="";
		ID="";
		activity=0;
		postedBy=0;
		LikedByAddress=0;
		numOfLikes=0;
		numOfComments=0;
		comments=0;
	}
	void ViewUser()
	{
		postedBy->ViewUser();
	}
	~Post()
	{
		if(ID)
			delete ID;
		if(text)
			delete text;
		if (activity)
			delete activity;
		if (comments)
			for (int i=0 ; i<numOfComments ; i++)
			{
				delete comments[i];
			}
	}
	char*GetID()
	{
		return ID;
	}
	void ReadPostDataFromFile(ifstream&fin)
	{
		char buffer[100];
		fin>>type;
		fin>>buffer;
		ID = Helper::GetStringFromBuffer(buffer);
		SharedDate.ReadDateFromFile(fin);
		fin.ignore('\n' , 10);
		fin.getline(buffer,100);
		text = Helper::GetStringFromBuffer(buffer);
		if (type==2)
		{
			activity = new Activity;
			activity->ReadActivityFromFile(fin);
		}
	}
	void SetSharedAddress(Object*shared)
	{
		this->postedBy = shared;
	}
	void LikePost(Object*like)
	{
		if (LikedByAddress==0)
		{
			LikedByAddress = new Object*[10];
		}
		LikedByAddress[numOfLikes] = like;
		numOfLikes++;
	}
	void PostComment(Comment*C)
	{
		if (comments==0)
		{
			comments = new Comment*[10];
		}
		comments[numOfComments] = C;
		numOfComments++;
	}
	virtual void ViewPost()
	{
		if (type==1)
		{
			cout<<"\n********************************************************************************\n";
			postedBy->ViewUser();
			cout<<"  Posted"<<endl;
			cout<<"\t";
			cout<<"\"";
			cout<<text;
			cout<<"\"";
			cout<<"\t";
			SharedDate.PrintDate();
			cout<<endl<<endl;
			cout<<"**************************************************************"<<endl;
			cout<<" |                        Comment Section                     |\n";
			cout<<"**************************************************************"<<endl;
			cout<<endl<<endl;
			for (int i=0 ; i<numOfComments ; i++)
			{
				comments[i]->PrintComment();
				cout<<endl;
			}
			cout<<endl<<endl;
			cout<<"\n********************************************************************************\n";

		}
		if (type==2)
		{
			cout<<"\n********************************************************************************\n";
			postedBy->ViewUser();
			activity->PrintActivity();
			cout<<endl<<endl;
			cout<<"\t";
			cout<<"\"";
			cout << text;
			cout<<"\"";
			cout<<"\t";
			SharedDate.PrintDate();
			cout<<endl<<endl;
			cout<<"**************************************************************"<<endl;
			cout<<" |                        Comment Section                     |\n";
			cout<<"**************************************************************"<<endl;
			cout<<endl;
			for (int i=0 ; i<numOfComments ; i++)
			{
				comments[i]->PrintComment();
				cout<<endl;
			}
			cout<<endl<<endl;
			cout<<"\n********************************************************************************\n";

		}
	}
	void ViewLikesList()
	{
		for (int i=0 ; i<numOfLikes ; i++)
		{
			LikedByAddress[i]->ViewUser();
			cout<<endl;
		}
	}
	void CheckDate()
	{
		int check = SharedDate.Date::CompareDate(Date::CurrentDate);
		if (check==1)
		{
			this->ViewPost();
		}
	}
	void CheckMemories()
	{
		if (SharedDate.CompareMemory(Date::CurrentDate)==1)
		{
			cout<<"We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\n";
			this->PrintMemory();
		}
		else
		{
			cout<<"No Memories to Show Of User"<<endl;
		}
	}
	void PrintMemory()
	{
		postedBy->ViewUser();
		cout<<"'s Memory\n";
		int Year = Date::CurrentDate.GetYear() - SharedDate.GetYear();
		cout<<Year <<" years ago"<<endl<<endl;
		this->ViewPost();
	}
};
class Memory:public Post
{
private:
	Post*OrignalPost;
	char*MemoryText;
public:
	Memory()
	{
		MemoryText="";
	}
	void ViewPost()
	{
		cout<<"**********************";
		OrignalPost->ViewUser();
		cout<<" Shared a Memory **********************";
		cout<<endl<<endl<<endl;
		cout<<"\t\""<<MemoryText<<"\""<<endl<<endl<<endl;
		OrignalPost->ViewPost();
	}
	void SetMemory(Post*ptr , char*text)
	{
		OrignalPost = ptr;
		MemoryText = Helper::GetStringFromBuffer(text);
	}
	~Memory()
	{
		delete MemoryText;
	}
};
class Page : public Object
{
private:
	char* ID;
	char* PageTitle;
	Post**Feed;
	int numOfPosts;
public:
	Page()
	{
		ID="";
		PageTitle="";
		Feed=0;
		numOfPosts=0;
	}
	~Page()
	{
		if (ID!="")
		{
			delete ID;
			ID="";
		}
		if (PageTitle!="")
		{
			delete PageTitle;
			PageTitle="";
		}
		if (Feed!=0)
		{
			delete Feed;
			Feed=0;
		}
	}
	void ReadPagesFromFile(ifstream& fin)
	{
		char tempBuffer[100];
		fin>>tempBuffer;
		ID = Helper::GetStringFromBuffer(tempBuffer);
		fin.getline(tempBuffer,100);
		PageTitle = Helper::GetStringFromBuffer(tempBuffer);
	}
	char* GetID()
	{
		return ID;
	}
	void ViewUser()
	{
		cout<<PageTitle;
	}
	void ViewPages()
	{
		cout<<ID<<"\t"<<PageTitle;
	}
	void PostOnFeed(Post*ToBeAdded)
	{
		if (Feed==0)
		{
			Feed = new Post*[10];
		}
		Feed[numOfPosts] = ToBeAdded;
		numOfPosts++;
	}
	void LatestPost()
	{
		if (Feed==0)
		{
			cout<<"Nothing on User's Feed from ";
			this->ViewUser();
			cout<<"\n\n";
		}
		else
		{
			for (int j=0 ; j<this->numOfPosts ; j++)
			{
				this->Feed[j]->CheckDate();
			}
		}
	}
	void ViewTimeLine()
	{
		this->ViewUser();
		cout<<"   ----TimeLine"<<endl<<endl;
		for (int i=0 ; i<numOfPosts ; i++)
		{
			cout<<"--------------------------------------------\n";
			Feed[i]->ViewPost();
		}
	}
};

class User : public Object
{
private:
	char* ID;
	char* FName;
	char* LName;
	Page**LikedPages;
	int numOfLikedPages;
	User**FriendList;
	int numOfFriends;
	Post**Feed;
	int numOfPosts;
public:
	User()
	{
		ID="";
		FName="";
		LName="";
		numOfLikedPages=0;
		numOfFriends=0;
		LikedPages =0;
		FriendList =0;
		Feed=0;
		numOfPosts=0;
	}
	~User()
	{
		if (ID!="")
		{
			delete ID;
			ID="";
		}
		if (FName!="")
		{
			delete FName;
			FName="";
		}
		if (LName!="")
		{
			delete LName;
			LName="";
		}
		if (LikedPages!=0)
		{
			delete LikedPages;
			LikedPages=0;
		}
		if (FriendList!=0)
		{
			delete FriendList;
			FriendList=0;
		}
		if (Feed!=0)
		{
			delete Feed;
			Feed=0;
		}
	}
	char* GetID()
	{
		return ID;
	}
	void ViewUser()
	{
		cout<<FName;
		cout<<" ";
		cout<<LName;
	}
	void ViewName()
	{
		cout<<ID<<"\t"<<FName<<" "<<LName;
	}
	void ReadUsersFromFile(ifstream& fin)
	{
		char tempBuffer[100];
		fin>>tempBuffer;
		ID = Helper::GetStringFromBuffer(tempBuffer);
		fin>>tempBuffer;
		FName = Helper::GetStringFromBuffer(tempBuffer);
		fin>>tempBuffer;
		LName = Helper::GetStringFromBuffer(tempBuffer);
	}
	void LikePages(Page* likepage)
	{
		if (LikedPages==0)
		{
			LikedPages = new Page*[10];
		}
		LikedPages[numOfLikedPages] = likepage;
		numOfLikedPages++;
	}
	void AddFriend(User* Friend)
	{
		if (FriendList==0)
		{
			FriendList = new User*[10];
		}
		FriendList[numOfFriends] = Friend;
		numOfFriends++;
	}
	void ViewFriendsList()
	{
		if (FriendList==0)
		{
			cout<<"No Friends of User :("<<endl;
		}
		for (int i=0 ; i<numOfFriends ; i++)
		{
			FriendList[i]->ViewName();
			cout<<endl;
		}
	}
	void ViewLikedPages()
	{
		if (LikedPages==0)
		{
			cout<<"No Liked Pages of User :("<<endl;
		}
		for (int i=0 ; i<numOfLikedPages ; i++)
		{
			LikedPages[i]->ViewPages();
			cout<<endl;
		}
	}
	void PostOnFeed(Post*ToBeAdded)
	{
		if (Feed==0)
		{
			Feed = new Post*[10];
		}
		Feed[numOfPosts] = ToBeAdded;
		numOfPosts++;
	}
	void ViewTimeLine()
	{
		this->ViewUser();
		cout<<"   ----TimeLine"<<endl<<endl;
		for (int i=0 ; i<numOfPosts ; i++)
		{
			Feed[i]->ViewPost();
		}
	}
	void Home()
	{
		if (FriendList==0)
		{
			cout<<"No Friends of User thus nothing to show on home \n\n\n";
		}
		else
		{
			for (int i=0 ; i<numOfFriends ; ++i)
			{
				this->FriendList[i]->LastestPost();
			}
			for (int j=0 ; j<numOfLikedPages ; j++)
			{
				this->LikedPages[j]->LatestPost();
			}
		}
	}
	void LastestPost()
	{
		if (Feed==0)
		{
			cout<<"Nothing on User's Feed from ";
			this->ViewUser();
			cout<<"\n\n";
		}
		else
		{
			for (int j=0 ; j<this->numOfPosts ; j++)
			{
				this->Feed[j]->CheckDate();
			}
		}
	}
	void SeeMemories()
	{
		if (numOfPosts==0 && Feed==0)
		{
			cout<<"No Posts and No Memories of User"<<endl;
		}
		for (int i=0 ; i<numOfPosts ; i++)
		{
			Feed[i]->CheckMemories();
		}
	}
	void ShareMemories(Post*PostPointer , char*text)
	{
		Memory*memory = new Memory;
		memory->SetMemory(PostPointer , text);
		this->PostOnFeed(memory);
	}
};
//CONTROLLER CLASS
class Facebook
{
private:
	Page** pages;
	User** users;
	char***TempFriendID;
	int total;
	int totalPages;
	int totalComments;
	Post**posts;
	Comment**comments;
public:
	Facebook()
	{
		pages=0;
		users=0;
		posts=0;
		comments=0;
	}
	~Facebook()
	{
		if (pages!=0)
		{
			for (int i=0 ; i<totalPages ; i++)
			{
				delete pages[i];
			}
			delete pages;
			pages=0;
		}
		if (users!=0)
		{
			for (int i=0 ; i<total ; i++)
			{
				delete users[i];
			}
			delete users;
			users=0;
		}
		for (int i=0 ; i<total ; i++)
		{
			delete TempFriendID[i];
		}
		delete TempFriendID;
		TempFriendID =0;
	}
	void Load()
	{
		LoadPagesFromFile();
		LoadUsersFromFile();
		LoadPostsFromFile();
		LoadCommentsFromFile();
	}
	void LoadPagesFromFile()
	{
		ifstream fin("pages.txt");
		fin>>totalPages;
		if (pages==0)
		{
			pages = new Page*[totalPages];
		}
		for (int i=0 ; i<totalPages ; i++)
		{
			pages[i] = new Page;
			pages[i]->ReadPagesFromFile(fin);
		}
		fin.close();
	}
	void LoadUsersFromFile()
	{
		ifstream fin("users.txt");
		fin>>total;
		if (users==0)
		{
			users = new User*[total];
		}
		char Buffer[100];
		TempFriendID = new char**[total];
		for (int i=0 ; i<total ; i++)
		{
			users[i] = new User;
			users[i]->ReadUsersFromFile(fin);
			TempFriendID[i] = new char*[10];
			int j=0;
			//Temporary storing users which are not created
			while (true)
			{
				fin>>Buffer;
				if (strcmp(Buffer , "-1")==0)
				{
					TempFriendID[i][j] = "\0";
					break;
				}
				TempFriendID[i][j] = Helper::GetStringFromBuffer(Buffer);
				TempFriendID[i][j+1] = nullptr;
				j++;
			}
			// Association of user with pages
			while (true)
			{
				fin>>Buffer;
				if (strcmp(Buffer , "-1")==0)
				{
					break;
				}
				Page*ptr = SearchPageByID(Buffer);
				users[i]->LikePages(ptr);
			}
		}
		fin.close();
		// Association of user with friends
		for (int j=0 ; j<total ; j++)
		{
			int k=0;
			while (strcmp(TempFriendID[j][k], "\0") != 0)
			{
				User*ptr = SearchUserByID(TempFriendID[j][k]);
				users[j]->AddFriend(ptr);
				k++;
			}
		}
	}
	void LoadPostsFromFile()
	{
		char UserID_OR_PageID[80];
		ifstream fileInput("SocialNetworkPosts.txt");
		if (!fileInput)
		{
			cout << "File Not Found";
		}
		else
		{
			fileInput.seekg(3 , ios::beg);
			int postData;
			fileInput >> postData;
			if (posts == 0)
			{
				posts = new Post * [postData];
			}
			for (int i = 0; i < postData; i++)
			{
				posts[i] = new Post;
				posts[i]->ReadPostDataFromFile(fileInput);
				fileInput>>UserID_OR_PageID;
				Object* PostedBy;
				PostedBy = SearchObjectByID(UserID_OR_PageID);
				posts[i]->SetSharedAddress(PostedBy);
				PostedBy->PostOnFeed(posts[i]);
				Object* LikedBy;
				while (true)
				{
					fileInput >> UserID_OR_PageID;
					if (Helper::strcmp(UserID_OR_PageID , "-1") == 0)
					{
						break;
					}
					LikedBy = SearchObjectByID(UserID_OR_PageID);
					posts[i]->LikePost(LikedBy);
				}
			}
		}
	}
	void LoadCommentsFromFile()
	{
		ifstream data("comments.txt");
		char postID[80],userID[80],text[80],CommentID[80];
		data>>totalComments;
		totalComments+=1;
		if (comments==0)
		{
			comments = new Comment*[totalComments];
		}
		for (int i=0 ; i<totalComments ; i++)
		{
			comments[i] = new Comment;
			data>>CommentID;
			data>>postID;
			Post*PostiD = SearchPostByID(postID);
			PostiD->PostComment(comments[i]);
			data>>userID;
			Object*SearchObject = SearchObjectByID(userID);
			data.getline(text , 80);
			comments[i]->SetComment(CommentID , text , SearchObject);
		}
		data.close();
	}
	Page* SearchPageByID(char* checker)
	{
		for (int i=0 ; i<totalPages ; i++)
		{
			if (Helper::strcmp(pages[i]->GetID() , checker)==0)
			{
				return pages[i];
			}
		}
		return nullptr;
	}
	User*SearchUserByID(char*checker2)
	{
		for (int i=0 ; i<total ; i++)
		{
			if (Helper::strcmp(users[i]->GetID() , checker2)==0)
			{
				return users[i];
			}
		}
		return nullptr;
	}
	Object*SearchObjectByID(char*id)
	{
		for (int i=0 ; i<totalPages ; i++)
		{
			if (Helper::strcmp(pages[i]->GetID() , id)==0)
			{
				return pages[i];
			}
		}
		for (int i=0 ; i<total ; i++)
		{
			if (Helper::strcmp(users[i]->GetID() , id)==0)
			{
				return users[i];
			}
		}
		return nullptr;
	}
	Post*SearchPostByID(char*PostCheck)
	{
		for (int i=0 ; i<11 ; i++)
		{
			if (Helper::strcmp(posts[i]->GetID() , PostCheck)==0)
			{
				return posts[i];
			}
		}
		return nullptr;
	}
};

int main ()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Facebook fb;
	fb.Load();
	cout<<"|*************************************************************|"<<endl;;
	cout<<"|                     WELCOME TO FACEBOOK                     |"<<endl;
	cout<<"|*************************************************************|"<<endl;
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|          Command : \t Set current User to U7              |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	User* CurrentUser = fb.SearchUserByID("u20");
	cout<<"\t\"";
	CurrentUser->ViewUser();
	cout<<" successfully set as current User \""<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|                Command : \t View Friends List             |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	CurrentUser->ViewUser();
	cout<<" - FriendList"<<endl<<endl;
	CurrentUser->ViewFriendsList();
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|            Command : \t View Liked Pages List             |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	CurrentUser->ViewName();
	cout<<" - Liked Pages"<<endl<<endl;
	CurrentUser->ViewLikedPages();
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|        Command : \t View Liked Post (Before Liking        |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	Post*postPtr = fb.SearchPostByID("post8");
	postPtr->ViewLikesList();
	postPtr->LikePost(CurrentUser);
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|        Command : \t View Liked Post (After Liking)        |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	postPtr->ViewLikesList();
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|               Command : \t Add A comment  (post 8)        |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	Comment*temp_Comment = new Comment;
	temp_Comment->SetComment("0" , "Thank You For the Wishes " , CurrentUser);
	postPtr->PostComment(temp_Comment);
	postPtr->ViewPost();
	Date::CurrentDate.SetCurrentDate(15 , 11 , 2017);
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|                    Command : \t View Home                 |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	CurrentUser->Home();
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|                   Command : \t View TimeLine              |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	CurrentUser->ViewTimeLine();
    cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|                    Command : \t View Memory               |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	Date::CurrentDate.SetCurrentDate(15 , 11 , 2019);
	CurrentUser->SeeMemories();
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|                  Command : \t Share A Memory              |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	Post*ptr = fb.SearchPostByID("post10");
	CurrentUser->ShareMemories(ptr , "Never thought I will be specialist in this field");
	CurrentUser->ViewTimeLine();
	Page*CurrentPage = fb.SearchPageByID("p1");
	CurrentPage->ViewTimeLine();
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|          Command : \t Set current User to U11             |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	CurrentUser = fb.SearchUserByID("u11");
	cout<<"\t\"";
	CurrentUser->ViewUser();
	cout<<" successfully set as current User \""<<endl<<endl;
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|                    Command : \t View Home                 |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	CurrentUser->Home();
	cout<<endl<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"|                   Command : \t View TimeLine              |"<<endl;
	cout<<"**************************************************************"<<endl<<endl;
	CurrentUser->ViewTimeLine();
	system("pause");
	return 0;
}