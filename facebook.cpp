#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class helper
{
public:
	static char* getstrigFromBuufer(char*New, char*copy)
	{
		int i = 0;
		New = new char[strlen(copy) +1];
		for (; copy[i] != '\0'; i++)
		{
			New[i] = copy[i];
		}
		New[i] = '\0';
		return New;
	}
	static void strcp(char*New, char*copy)
	{
		int i = 0;
		for (; copy[i] != '\0'; i++)
		{
			New[i] = copy[i];
		}
		New[i] = '\0';
	}
	static 	bool strcomp(char*copy, char*compare)
	{
		int a = 0;
		if (strlen(compare) == strlen(copy))
		{
			for (int i = 0; compare[i] != '\0'&&a == 0; i++)
			{
				if (copy[i] != compare[i])
				{
					a = 1;
				}
			}
		}
		else
			a = 1;

		if (a == 0)
			return true;
		else
			return false;
	}
};



class object
{
	char*id;
public:

	~object()
	{
		if (id != nullptr)
			delete[]id;
	}


	object()
	{
		id = nullptr;
	}


	char* getObjId()
	{
		return id;
	}


	void setObjId(char*pId)
	{
		if (id != nullptr)
		{
			if (strlen(id) != strlen(pId))
			{
				delete[]id;
				id = helper::getstrigFromBuufer(id, pId);
			}
			else
			{
				helper::strcp(id, pId);
			}
		}
		else
			id = helper::getstrigFromBuufer(id, pId);
	}


	char getObjIndex(int i)
	{
		return id[i];
	}


	virtual void print()
	{
		cout << id;
		cout << endl;
	}


	virtual void PrintNames()
	{

	}


	



};



class date
{
private:
	int day;
	int month;
	int year;
public:
	date(int d = 1, int m = 1, int y = 1960)
	{
		day = d;
		month = m;
		year = y;
	}
	void setDate(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	static date CurrentDate;
	bool operator==(date&p)
	{
		if (day == p.day&&month == p.month&&year == p.year)
		{
			return true;
		}
		else
			return false;
	}
	static void SetCurrentDate(int d, int m, int y)
	{
		CurrentDate.day = d;
		CurrentDate.month = m;
		CurrentDate.year = y;
	}
	static void PrintCurrentDate()
	{
		cout << CurrentDate.day << "/" << CurrentDate.month << "/" << CurrentDate.year;
		cout << endl << endl;
	}
	void printSharedDate()
	{
		cout << day << "/" << month << "/" << year;
	}
	int getDay()
	{
		return day;
	}
	int getMonth()
	{
		return month;
	}
	int getyear()
	{
		return year;
	}
};


class comment :public object
{
	char*text;
	object*commmentby;
public:


	comment()
	{
		commmentby = nullptr;
		text = nullptr;
	}


	void SetText(char*buffer)
	{
		text = helper::getstrigFromBuufer(text, buffer);
	}


	~comment()
	{
		if (text != nullptr)
			delete[]text;
		
	}


	void SetCommentBy(object*ptr)
	{
		commmentby = ptr;
	}


	void print()
	{
		cout << getObjId();
		cout << endl;
		commmentby->print();
		cout << endl;
		cout << text << endl;
	}


	void printComments()
	{
	//	commentedOn->PrintPostAndDate();
		cout << endl;
		cout << "\t";
		if (commmentby != nullptr)
		{
			commmentby->PrintNames();
		}
		cout << " " << "wrote"<<" ";
		for (int i = 0; text[i] != '\0'; i++)
		{
			cout << text[i];
		}
	}



};






class post :public object
{
	date sharedDate;
	char*text;
	object*sharedBy;
	comment**comments;
	int CommentSize;
	object**likedBy;
	int LikedBySize;
public:

	post()
	{
		text = nullptr;
		sharedBy = nullptr;
		likedBy = nullptr;
		comments = nullptr;
		CommentSize = 0;
		LikedBySize = 0;
	}


	~post()
	{
		if (text != nullptr)
		{
			delete[] text;
		}
		if (comments != nullptr)
		{
			for (int i = 0; comments[i] != nullptr; i++)
			{
				delete[]comments[i];
			}
			delete[]comments;
		}
		if (likedBy != nullptr)
		{
			delete[]likedBy;
		}
	}


	char*GetText()
	{
		return text;
	}


	char*GetSharedId()
	{
		return sharedBy->getObjId();
	}


	void printSearch()
	{
		cout << getObjId()<<"-" << " " << text;
		cout << endl;
	}


	void printComments()
	{
		for (int i = 0; comments[i] != nullptr; i++)
		{
			comments[i]->printComments();
		}
	}


	void SetCommentSize(int size)
	{
		comments = new comment*[size];
	}


	void printDate()
	{
		cout << "(";
		sharedDate.printSharedDate();
		cout << ")";
	}


	void SetText(char*buffer)
	{
		text = helper::getstrigFromBuufer(text, buffer);
	}


	void SetCommentEndSize()
	{
		comments[CommentSize] = nullptr;
	}


	void SetComments(comment*curr)
	{
		comments[CommentSize] = curr;
		CommentSize++;
	}


	void SetDate(int d, int m, int y)
	{
		sharedDate.setDate(d, m, y);
	}


	void setSharedBy(int i)
	{
		sharedBy = new object[i];
	}


	void SetLikedBy(int i)
	{
		likedBy = new object*[i];
	}


	object*getSharedBy()
	{
		return sharedBy;
	}


	void print()
	{
		cout << text << endl;
		for (int i = 0; comments[i] != nullptr; i++)
		{
			comments[i]->printComments();
		}
		
	}


	void Setshared(object*ptr)
	{
		sharedBy = ptr;

	}


	void GetLikedFromFile(char*buffer, istream&fin)
	{
		int b = 0;
		for (int i = 0; b == 0; i++)
		{
			fin >> buffer;
			if (buffer[0] != '-')
			{

			}
			else
			{
				b = 1;
				likedBy[i] = nullptr;
				//fin >> s;
			}
		}
	}


	void SetLikedBy(object*current)
	{
		likedBy[LikedBySize] = current;
		LikedBySize++;
	}


	void SetLikedBySize()
	{
		likedBy[LikedBySize] = nullptr;
	}


	void PrintPostAndDate()
	{
		cout << text << " "; printDate();
	}


	void PrintHome()
	{
		PrintPostAndDate();
		printComments();
	}


	char *returnPostId(int i)
	{
		return getObjId();
	}


	void ViewLikedList()
	{
		if (likedBy != nullptr)
		{
			for (int i = 0; likedBy[i] != nullptr; i++)
			{
				likedBy[i]->print();
				cout << endl;
			}
		}
	}


	void LikePost(object*curr)
	{
		SetLikedBy(curr);
		SetLikedBySize();
	}


	void PostComment(object*curr,char*text,int NoOfComments)
	{
		comment*c1 = new comment;
		std::string s = std::to_string(NoOfComments);
		char str[4];
		str[0] = 'c';
		int a = 0;
		int i = 1;
		for (; s[a] != '\0'; i++)
		{
			str[i] = s[a];
			a++;
		}
		str[i] = '\0';
		c1->setObjId(str);
		c1->SetText(text);
		c1->SetCommentBy(curr);
		SetComments(c1);
		SetCommentEndSize();
	}


	bool CompareDate()
	{
		if (sharedDate == date::CurrentDate)
			return true;
		else
			return false;
	}



};





class pages:public object
{
	//char*id;
	char*title;
	post**timeline;
	int TimeLineSize;
//	comment**comments;

public:


	pages()
	{
		title = nullptr;
		timeline = nullptr;
		TimeLineSize = 0;
	}


	~pages()
	{
		if (title != nullptr)
			delete[]title;
		if (timeline != nullptr)
		{
			for (int i = 0; timeline[i] != nullptr; i++)
			{
				delete[]timeline[i];
			}
			delete[]timeline;
		}
	}


	void setName(char*buffer)
	{
		int j = 0;
		title = helper::getstrigFromBuufer(title,buffer);
	}


	void print()
	{
		cout << getObjId();
		cout << "-"; cout << " ";
		for (int i = 1; title[i] != '\0'; i++)
		{
			cout << title[i];
		}
	}


	void SetPostList(post*curr)
	{
		static int a = 0;
		timeline[TimeLineSize] = curr;
		TimeLineSize++;
	}


	void printTitle()
	{
		for (int i = 1; title[i] != '\0'; i++)
		{
			cout << title[i];
		}
	}


	void SetPostSize()
	{
		timeline = new post*[10];
	}


	void PrintNames()
	{
		for (int i = 1; title[i] != '\0'; i++)
			cout << title[i];
	}


	char*GetPostID(int i)
	{
		return timeline[i]->returnPostId(i);
	}


	void PrintPosts()
	{
		for (int i = 0; timeline[i] != nullptr; i++)
		{
			timeline[i]->PrintPostAndDate();
			cout << endl;
		}
	}


	void SetTimeLineSize()
	{
		timeline[TimeLineSize] = nullptr;
	}


	post*GetTimeLine(int i)
	{
		return timeline[i];
	}


	char* GetTitle()
	{
		return title;
	}


	char*GetTimeLineId(int i)
	{
		return timeline[i]->getObjId();
	}


	void PrintTimeline()
	{
		for (int i = 0; timeline[i] != nullptr; i++)
		{
			timeline[i]->PrintPostAndDate();
			timeline[i]->printComments();
			cout << endl << endl;
		}
	}



};



class users :public object
{
	char* fname; char* lname;
	users**friendlist;
	char**friendId;
	char**pageId;
	pages** likedPages;
	post**timeline;
	int TimeLineSize;
	int LikedPagesSize;
	int FriendsListSize;
	int FriendIdSize;
	int PageIdSize;


public:


	users()
	{
		fname = nullptr; lname = nullptr; friendlist = nullptr; friendId = nullptr;
		timeline = nullptr; pageId = nullptr; likedPages = nullptr; LikedPagesSize = 0; FriendsListSize = 0; FriendIdSize = 0;
		PageIdSize = 0; TimeLineSize = 0;
	}


	~users()
	{
		if (fname != nullptr)
		{
			delete[]fname;
		}
		if (lname != nullptr)
		{
			delete[]lname;
		}
		if (friendId != nullptr)
		{
			for (int i = 0; friendId[i] != nullptr; i++)
			{
				delete[]friendId[i];
			}
			delete[]friendId;
		}
		if (pageId != nullptr)
		{
			for (int i = 0; pageId[i] != nullptr; i++)
			{
				delete[]pageId[i];
			}
			delete[]pageId;
		}
		if (friendlist != nullptr)
		{
			delete[]friendlist;
		}
		if (likedPages != nullptr)
		{
			delete[]likedPages;
		}
		if (timeline != nullptr)
		{
			for (int i = 0; timeline[i] != nullptr; i++)
			{
				delete[]timeline[i];
			}
			delete[]timeline;
		}
	}


	char*getFname()
	{
		return fname;
	}


	char*getlname()
	{
		return lname;
	}


	char**friendid()
	{
		return friendId;
	}


	void setfname(char*pfname)
	{
		int i = 0;
		fname = new char[strlen(pfname) + 1];
		for (; pfname[i] != '\0'; i++)
		{
			fname[i] = pfname[i];
		}
		fname[i] = '\0';
	}


	void setlname(char*plname)
	{
		int i = 0;
		lname = new char[strlen(plname) + 1];
		for (; plname[i] != '\0'; i++)
		{
			lname[i] = plname[i];
		}
		lname[i] = '\0';
	}


	void setfreindListSize()
	{
		friendId = new char*[10];
	}


	void setPagesdIdSize()
	{
		pageId = new char*[10];
	}


	void setfriendsIdFromBuffer(char*buffer)
	{
		friendId[FriendIdSize] = helper::getstrigFromBuufer(friendId[FriendIdSize], buffer);
		FriendIdSize++;
	}


	void SetFriendIdEndSize()
	{
		friendId[FriendIdSize] = nullptr;
	}


	void SetPageIdEndSize()
	{
		pageId[PageIdSize] = nullptr;
	}


	void setpageIdFromBuffer(char*buffer)
	{
		pageId[PageIdSize] = helper::getstrigFromBuufer(pageId[PageIdSize], buffer);
		PageIdSize++;
	}


	void print()
	{
		cout << getObjId() << " -" << fname << " " << lname << " ";
	}


	char*GetFriendId(int i)
	{
		return friendId[i];
	}


	void setFriendsListSize()
	{
		friendlist = new users*[10];
	}


	void setLikedPagesSize()
	{
		likedPages = new pages*[10];
	}


	void setFriendList(users*curr)
	{
		friendlist[FriendsListSize] = curr;
		FriendsListSize++;
	}


	void SetPostList(post*curr)
	{
		timeline[TimeLineSize] = curr;
		TimeLineSize++;
	}


	void setPageList(pages*curr)
	{
		likedPages[LikedPagesSize] = curr;
		LikedPagesSize++;
	}


	void SetPageEndSize()
	{
		likedPages[LikedPagesSize] = nullptr;
	}


	void SetPostEndSize()
	{
		timeline[TimeLineSize] = nullptr;
	}


	void SetFriendListEndSize()
	{
		friendlist[FriendsListSize] = nullptr;
	}


	void SetPostSize()
	{
		timeline = new post*[10];
	}


	void printFriends()
	{
		for (int i = 0; friendlist[i] != nullptr; i++)
		{
			cout << friendlist[i]->getObjId() << "-" << "\t" << friendlist[i]->getFname() << " " << friendlist[i]->getlname();
			cout << endl;
		}
	}


	void printPages()
	{
		for (int i = 0; i < LikedPagesSize; i++)
		{
			cout << likedPages[i]->getObjId() << "-" << " "; likedPages[i]->printTitle();
			cout << endl;
		}
	}


	void SetTimeLineSize()
	{
		timeline[TimeLineSize] = nullptr;
	}


	void PrintPosts()
	{
		for (int i = 0; timeline[i] != nullptr; i++)
		{
			timeline[i]->PrintPostAndDate();
			cout << endl;
		}
	}


	char* GetPageId(int i)
	{
		return pageId[i];
	}


	post*getTimeline(int i)
	{
		return timeline[i];
	}


	char*getTimeLineId(int i)
	{
		return timeline[i]->getObjId();
	}


	void PrintTimeline()
	{
		for (int i = 0; timeline[i] != nullptr; i++)
		{
			timeline[i]->PrintPostAndDate();
			timeline[i]->printComments();
			cout << endl << endl;
		}
	}


	void PrintNames()
	{
		cout << getFname() << " " << lname;
	}


	void printNameAndSharedBy()
	{
		cout<<getFname() << " " << getlname() << " " << "shared" << " ";
	}


	void SharePost(post*curr)
	{
		post object;
	
		SetPostList(curr);
		SetPostEndSize();
	}


	void ViewHome()
	{

		for (int i = 0; friendlist[i] != nullptr; i++)
		{
			for (int j = 0; friendlist[i]->getTimeline(j) != nullptr; j++)
			{
				if (friendlist[i]->getTimeline(j)->CompareDate())
				{
					friendlist[i]->printNameAndSharedBy();
					friendlist[i]->getTimeline(j)->PrintHome();
					cout << endl; cout << endl;
				}
			}
		}
		for (int i = 0; likedPages[i] != nullptr; i++)
		{
			for (int j = 0; likedPages[i]->GetTimeLine(j) != nullptr; j++)
			{
				if (likedPages[i]->GetTimeLine(j)->CompareDate())
				{
					friendlist[i]->printNameAndSharedBy();
					friendlist[i]->getTimeline(j)->PrintHome();
					cout << endl; cout << endl;
					cout << endl << endl;
				}
			}
		}
		date::SetCurrentDate(date::CurrentDate.getDay() - 1, date::CurrentDate.getMonth(), date::CurrentDate.getyear());
		int s = 0;
		for (int i = 0; friendlist[i] != nullptr; i++)
		{
			for (int j = 0; friendlist[i]->getTimeline(j) != nullptr; j++)
			{
				if (friendlist[i]->getTimeline(j)->CompareDate())
				{
					friendlist[i]->printNameAndSharedBy();
					friendlist[i]->getTimeline(j)->PrintHome();
					cout << endl; cout << endl;
				}
				else
				{
					s = 0;
				}
			}
		}
		for (int i = 0; likedPages[i] != nullptr; i++)
		{
			for (int j = 0; likedPages[i]->GetTimeLine(j) != nullptr; j++)
			{
				if (likedPages[i]->GetTimeLine(j)->CompareDate())
				{
					friendlist[i]->printNameAndSharedBy();
					friendlist[i]->getTimeline(j)->PrintHome();
					cout << endl << endl;
				}
			}
		}
	}


	void LikePage(pages*curr)
	{
		setPageList(curr);
		SetPageEndSize();
	}



};




class facebook
{
	users**user;
	pages**pg;
	users*CurrentUser;
	pages*currentPage;
	post*currentPost;
	int noOfUsers;
	int NoOfPages;
	int NOfPosts;
	int NoOfComments;
	//post**pst;


public:


	facebook() {
		user = nullptr;
		pg = nullptr;
		noOfUsers = 0;
		NoOfPages = 0;
		NOfPosts = 0;
		CurrentUser = nullptr;
		currentPage = nullptr;
		currentPage = nullptr;
	}


	~facebook() {
		if (user != nullptr)
		{
			for (int j = 0; j<noOfUsers; j++)
			{
				delete user[j];
			}
			delete[]user;
		}
		if (pg != nullptr)
		{
			for (int i = 0; i < NoOfPages; i++)
			{
				delete pg[i];
			}
			delete[]pg;
		}
	}


	void LoadFiles()
	{
		ifstream fin;
		fin.open("Users.txt");
		char buffer[80];
		setUsersFromFile(buffer, fin);
		fin.close();
		ifstream finn;
		finn.open("pages.txt");
		SetPagesFromFile(finn, buffer);
		finn.close();
		ifstream finnn;
		int noOfPages = 0;
		finnn.open("Posts.txt");
		int NoOFPosts = 0;
		setPostFromFile(finnn,buffer, noOfUsers, NoOfPages);
		fin.close();
		ifstream Fin;
		Fin.open("Comments.txt");
		int NoOfComment = 0;
		SetCommentFromFile(Fin, buffer, noOfUsers, NoOfPages);
		fin.close();

	}


	bool stringCompare(char*string, char*compare)
	{
		int a = 0;
		int count = 0;
		int count1 = 0;
		int flag = 0;
		for (int i = 0; string[i] != '\0'&&flag == 0; i++)
		{
			count = 0;
			count1++;
			if (string[i] == compare[count])
			{
				for (int z = i; string[z] != '\0'&&a == 0; z++)
				{
					if (string[z] == compare[count])
					{
						count++;
					}
					else
					{
						a = 1;
					}
					if (count == strlen(compare))
						flag = 1;
				}
			}
		}
		if (flag == 1)
			return true;
		else
			return false;
	}


	void SetPagesFromFile(ifstream&fin, char*buffer)
	{
		int N = 0;
		fin >> N;
		NoOfPages = N;
		pg = new pages*[NoOfPages];
		for (int i = 0; i < NoOfPages; i++)
		{
			pg[i] = GetPageFromFile(fin,pg[i], buffer);
		}
		for (int i = 0; i < NoOfPages; i++)
		{
			//pg[i]->print();
			//cout << endl;
		}
	}


	pages* GetPageFromFile(ifstream&fin,pages*pg,char*buffer)
	{
		pg = new pages;
		fin >> buffer;
		pg->setObjId(buffer);
		fin.getline( buffer,80);
		pg->setName(buffer);
		return pg;
	}


	users** setUsersFromFile(char*buffer, ifstream&fin)
	{
		int N;
		fin >> N;
		noOfUsers = N;
		user = new users*[noOfUsers];
		for (int i = 0; i < noOfUsers; i++)
		{
			user[i] = getUserFromFile(user[i], buffer, fin);
		}
		for (int i = 0; i < noOfUsers; i++)
		{
	//		user[i]->print();
	//		cout << endl;
		}
		return user;
	}


	users*getUserFromFile(users*current, char*buffer, ifstream&fin)
	{
		current = new users;
		fin >> buffer;
		current->setObjId(buffer);
		fin >> buffer;
		current->setfname(buffer);
		fin >> buffer;
		current->setlname(buffer);
		current->setfreindListSize();
		int a = 0; int s = 0; int size = 0;
		for (int i = 0; a == 0; i++)
		{
			fin >> buffer;
			if (buffer[0] != '-')
			{
				current->setfriendsIdFromBuffer(buffer);
			}
			else
			{
				a = 1;
				current->SetFriendIdEndSize();
				//fin >> s;
			}
		}
		//	friends=current->arrsize(friends);
		current->setPagesdIdSize();
		int b = 0;
		for (int i = 0; b == 0; i++)
		{
			fin >> buffer;
			if (buffer[0] != '-')
			{
				current->setpageIdFromBuffer(buffer);
			}
			else
			{
				b = 1;
				current->SetPageIdEndSize();
				//fin >> s;
			}
		}
	
		return current;
	}


	void SetCurrentUser(char* Id)
	{
		int i = 0;
		int a = 0;
		for (; i < noOfUsers && a==0; i++)
		{
			if (strcomp(Id,user[i]->getObjId()))
			{
				a = 1;
				cout << user[i]->getFname() << " " << user[i]->getlname()<<" ";
			}
		}
		cout << "successfully selected as current user\n";
		if (a == 1)
		{
			CurrentUser=user[i - 1];
		}
		cout << endl << endl;
	}


	void SetCurrentPage(char* Id)
	{
		int i = 0;
		int a = 0;
		for (; i < NoOfPages && a == 0; i++)
		{
			if (strcomp(Id, pg[i]->getObjId()))
			{
				a = 1;
	//			cout << pg[i]->getObjId()<<" ";
			}
		}
	//	cout << "successfully selected as current page\n";
		if (a == 1)
		{
			currentPage= pg[i - 1];
		}

	}


	bool strcomp(char*copy, char*compare)
	{
		int a = 0;
		if (strlen(compare) == strlen(copy))
		{
			for (int i = 0; compare[i] != '\0'&&a == 0; i++)
			{
				if (copy[i] != compare[i])
				{
					a = 1;
				}
			}
		}
		else
			a = 1;

		if (a == 0)
			return true;
		else
			return false;
	}


	void ViewFriendList()
	{
		int size = 0;
		cout << CurrentUser->getFname() << " " << CurrentUser->getlname() << "-" << "friend list\n";
		CurrentUser->setFriendsListSize();
		for (int i = 0; i < noOfUsers; i++)
		{
			for (int j = 0; CurrentUser->GetFriendId(j) != '\0'; j++)
			{
				if (strcomp(CurrentUser->GetFriendId(j), user[i]->getObjId()))
				{
					CurrentUser->setFriendList(user[i]);
				}
			}
		}
		CurrentUser->SetFriendListEndSize();
		CurrentUser->printFriends();
		cout << endl << endl;
	}


	void ViewLikedPages()
	{
		CurrentUser->setLikedPagesSize();
		for (int i = 0; i < NoOfPages; i++)
		{
			for (int j = 0; CurrentUser->GetPageId(j) != '\0'; j++)
			{
				if (strcomp(CurrentUser->GetPageId(j), pg[i]->getObjId()))
				{
					CurrentUser->setPageList(pg[i]);
				}
			}
		}
		CurrentUser->SetPageEndSize();
		CurrentUser->printPages();
		cout << endl << endl;
	}


	void ViewTimeline()
	{
		CurrentUser->PrintTimeline();
		cout << endl << endl;
	}


	void getpostsFromFile(char*buffer,ifstream&fin,int NoOfPages,int NoOfUsers,int noOfPages)
	{
		post*pst = new post;
		int day, month, year;
		fin >> buffer;
		pst->setObjId(buffer);
		fin >> day;
		fin >> month;
		fin >> year;
		pst->SetDate(day, month, year);
		fin.ignore();
		fin.getline(buffer, 80);
		pst->SetText(buffer);
		fin >> buffer;
		for (int i = 0; i < NoOfUsers; i++)
		{
			if (strcomp(user[i]->getObjId(), buffer))
			{
				pst->Setshared(user[i]);
			}
		}
		for (int i = 0; i < NoOfPages; i++)
		{
			if (strcomp(pg[i]->getObjId(), buffer))
			{
				pst->Setshared(pg[i]);
			}
		}
		int b = 0;
		pst->SetLikedBy(10);
		for (int i = 0; b == 0; i++)
		{

			fin >> buffer;
			if (buffer[0] != '-')
			{
				for (int i = 0; i < NoOfUsers; i++)
				{
					if (strcomp(user[i]->getObjId(), buffer))
					{
						pst->SetLikedBy(user[i]);
					}
				}
				for (int i = 0; i < NoOfPages; i++)
				{
					if (strcomp(pg[i]->getObjId(), buffer))
					{
						pst->SetLikedBy(pg[i]);
					}
				}

			}
			else
			{
				b = 1;
			}
		}
		for (int i = 0; i < NoOfUsers; i++)
		{
			if (strcomp(pst->GetSharedId(), user[i]->getObjId()))
			{
				user[i]->SetPostList(pst);
			}
		}
		for (int i = 0; i < NoOfPages; i++)
		{
			if (strcomp(pst->GetSharedId(), pg[i]->getObjId()))
			{
				pg[i]->SetPostList(pst);
			}
		}
		pst->SetLikedBySize();
	//	pst->print();
   
	}


	void setPostFromFile(ifstream&fin, char*buffer,  int NoOfUsers, int NoOfPages)
	{
		int N = 0;
		fin >> N;
		NOfPosts = N;
		for (int i = 0; i < NoOfUsers; i++)
		{
			user[i]->SetPostSize();
		}
		for (int i = 0; i < NoOfPages; i++)
		{
			pg[i]->SetPostSize();
		}
		for (int i = 0; i < NOfPosts; i++)
		{
			getpostsFromFile(buffer, fin, NOfPosts, NoOfUsers, NoOfPages);
		}
		for (int i = 0; i < NoOfUsers; i++)
		{
			user[i]->SetTimeLineSize();
		}
		for (int i = 0; i < NoOfPages; i++)
		{
			pg[i]->SetTimeLineSize();
		}
	}


	void SetCommentFromFile(ifstream&fin, char*buffer, int NoOFUsers, int NoOFPages)
	{
		int N = 0;
		fin >> N;
		NoOfComments = N;
		for (int i = 0; i < NoOFUsers; i++)
		{
			for (int j = 0; user[i]->getTimeline(j) != nullptr; j++)
			{
				user[i]->getTimeline(j)->SetCommentSize(10);
			}
		}
		for (int i = 0; i < NoOFPages; i++)
		{
			for (int j = 0; pg[i]->GetTimeLine(j) != nullptr; j++)
			{
				pg[i]->GetTimeLine(j)->SetCommentSize(10);
			}
		}

		for (int i = 0; i < NoOfComments; i++)
		{
			comment*ptr = new comment;
			fin >> buffer;
			ptr->setObjId(buffer);
			fin >> buffer;
			for (int i = 0; i < NoOFUsers; i++)
			{
				for (int j = 0; user[i]->getTimeline(j) != nullptr; j++)
				{
					if (strcomp(user[i]->getTimeLineId(j), buffer))
					{
						user[i]->getTimeline(j)->SetComments(ptr);
						//	user[i]->SetComments(ptr);
					}
				}
			}
			for (int i = 0; i < NoOFPages; i++)
			{
				for (int j = 0; pg[i]->GetTimeLine(j) != nullptr; j++)
				{
					if (strcomp(pg[i]->GetTimeLineId(j), buffer))
					{
						pg[i]->GetTimeLine(j)->SetComments(ptr);
						//	pg[i]->setComments(ptr)
					}
				}
			}

			fin >> buffer;
			for (int i = 0; i < NoOFUsers; i++)
			{
				if (strcomp(buffer, user[i]->getObjId()))
				{
					ptr->SetCommentBy(user[i]);
				}
			}
			for (int i = 0; i < NoOFPages; i++)
			{
				if (strcomp(buffer, pg[i]->getObjId()))
				{
					ptr->SetCommentBy(pg[i]);
				}
			}
			fin.getline(buffer, 80);;
			ptr->SetText(buffer);
//			ptr->print();
//			cout << endl;
		}
		for (int i = 0; i < NoOFUsers; i++)
		{
			for (int j = 0; user[i]->getTimeline(j) != nullptr; j++)
			{
				user[i]->getTimeline(j)->SetCommentEndSize();
			}
		}
		for (int i = 0; i < NoOFPages; i++)
		{
			for (int j = 0; pg[i]->GetTimeLine(j) != nullptr; j++)
			{
				pg[i]->GetTimeLine(j)->SetCommentEndSize();
			}
		}
	
	}


	void setCurrentPost(char*Id)
	{
		for (int i = 0; i < noOfUsers; i++)
		{
			for (int j = 0; user[i]->getTimeline(j) != nullptr; j++)
			{
				if (strcomp(Id, user[i]->getTimeLineId(j)))
				{
					currentPost= user[i]->getTimeline(j);
					return;
				}
			}
		}
		for (int i = 0; i < NoOfPages; i++)
		{
			for (int j = 0; pg[i]->GetTimeLine(j) != nullptr; j++)
			{
				if (strcomp(Id, pg[i]->GetTimeLineId(j)))
				{
					currentPost= pg[i]->GetTimeLine(j);
					return;
				}
			}

		}
	}


	void search(char*p)
	{
		cout << "Users:\n";
		for (int i = 0; i<noOfUsers; i++)
		{
				if (strcomp(user[i]->getFname(), p))
				{
					user[i]->print();
					cout << endl;
				}
				if (strcomp(user[i]->getlname(), p))
				{
					user[i]->print();
					cout << endl; cout << endl;
				}
		}
		cout << "Pages:\n";
		for (int i = 0; i<NoOfPages; i++)
		{
				if (stringCompare(pg[i]->GetTitle(), p))
				{
					pg[i]->print();
					cout << endl;
					cout << endl;
				}
		}
		
	}


	void LikePost()
	{
		currentPost->LikePost(CurrentUser);
		currentPost->ViewLikedList();
		cout << endl << endl;
	}


	void ViewPage(char*id)
	{
		SetCurrentPage(id);
		currentPage->PrintTimeline();
		cout << endl << endl;
	}


	void LikePage(char*id)
	{

		SetCurrentPage(id);
		CurrentUser->LikePage(currentPage);
		CurrentUser->printPages();
		cout << endl << endl;
	}


	void ViewPostLikedList(char*id)
	{
		setCurrentPost(id);
		currentPost->ViewLikedList();
		cout << endl << endl;
	
	}


	void sharePost(char*id)
	{
		setCurrentPost(id);
		post copy;
		copy.setObjId(currentPost->getObjId());
		copy.SetText(currentPost->GetText());
		copy.SetDate(date::CurrentDate.getDay(), date::CurrentDate.getMonth(), date::CurrentDate.getyear());
		copy.SetCommentSize(1);
		copy.SetCommentEndSize();
		post*pointer = &copy;
		CurrentUser->SharePost(pointer);
		CurrentUser->PrintTimeline();
		cout << endl << endl;
	
	}


	void PostComment(char*id,char*comment)
	{
		setCurrentPost(id);
		NoOfComments++;
		currentPost->PostComment(CurrentUser, comment,NoOfComments);
		currentPost->print();
		cout << endl << endl << endl << endl;
	}
	

	void ViewHome()
	{
		CurrentUser->ViewHome();
		cout << endl << endl;
	}




};
date date::CurrentDate;

int main()
{
	facebook fb;
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.LoadFiles();
	fb.SetCurrentUser("u7");
	cout << "Command: Set Current System Date 15/11/2017\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	date::SetCurrentDate(15, 11, 2017);
	cout << "system date: \t";
	date::PrintCurrentDate();
	cout << "Command: View friend list\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.ViewFriendList();
	cout << "Command: View Liked Pages list\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.ViewLikedPages();
	cout << "Command: View Timeline\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.ViewTimeline();
	cout << "Command: View Page\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.ViewPage("p1");
	cout << "Command: View Post Likes\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.ViewPostLikedList("post5");
	cout << "Command: Like Post\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.LikePost();
	cout << "Command: Like Page\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.LikePage("p8");
	cout << endl << endl;
	cout << "Command: Share Post\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.sharePost("post5");
	cout << "Command: PostComment on post5\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.PostComment("post8", "Thanks for the wishes.");
	cout << "Command: View Home of last 24 hours\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.ViewHome();
	cout << "Command: Search Ali";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	fb.search("Ali");//

	system("PAUSE");//
}   