Facebook Simulation Program
Description:
This is a C++ program simulating basic functionalities of a social media platform like Facebook. It allows users to create accounts, like pages, add friends, post statuses, comment on posts, like posts, view timelines, view memories, and share memories. Users can interact with posts from both friends and pages they have liked.

Components:
Classes:

Facebook: Controls the overall functionality of the social network.
User: Represents a user account with attributes like ID, first name, last name, liked pages, friend list, and posts.
Page: Represents a page account with attributes like ID, page title, and posts.
Post: Represents a post with attributes like ID, text, shared date, activity, posted by user or page, likes, comments, etc.
Comment: Represents a comment on a post with attributes like comment ID, text, and user who posted it.
Memory: Represents a memory post, a special type of post shared by users.
Helper: Provides utility functions like string manipulation.
Functionality:

Loading Data: Loads data of users, pages, posts, and comments from files.
User Interaction: Allows users to view friends list, liked pages, like posts, comment on posts, view timeline, view memories, share memories, etc.
Simulation: Simulates interactions within the social network platform based on user commands.
File Input:

users.txt: Contains user data like ID, first name, last name, and friend IDs.
pages.txt: Contains page data like ID and page title.
SocialNetworkPosts.txt: Contains post data including post type, ID, text, shared date, liked user IDs, etc.
comments.txt: Contains comment data including comment ID, post ID, user ID, and comment text.
How to Run:
Ensure all necessary source files are available.
Compile the source code using a C++ compiler (e.g., g++, Visual Studio).
Run the compiled executable file.
Follow the on-screen instructions to interact with the program.
Sample Commands:
Set current user to a specific user (e.g., "U7").
View friends list.
View liked pages list.
View liked post before and after liking.
Add a comment to a post.
View home timeline.
View user's timeline.
View memories.
Share a memory.
View page timeline.
Additional Notes:
This program is a basic simulation and does not include advanced features like authentication, real-time updates, messaging, etc.
It is designed for educational purposes to demonstrate object-oriented programming concepts and file handling in C++.
For a fully functional social media platform, additional features and robustness would be necessary.
