// moviebot.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "moviebot.h"
//#include <Rcpp.h>
#include "odbcsql.cpp"

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

	//beheer bulk
	string actor = "INSERT INTO Actor (ActorID, Name, Gender) values (actorid, actorname, 0)";
	string movie = "INSERT INTO Movies(Movie, Year, Studio, SerieName, SerieSeason, EpisodeNumber, EndSeason) VALUES(movieid, year, studio, serie, season, episode, endseason)";
	string directors = "INSERT INTO Directors(name) VALUES(director)";

	//selecting id
	string movieid ="SELECT MovieID FROM Movies WHERE movie = ’some movie name’";
	string actorid ="SELECT ActorID FROM Actors WHERE actor = ’some actor or actress name’";
	string directorid ="SELECT DirectorID FROM Directors WHERE director = ’some director name’";
		
	//beheer inserts looped
	string roles = "INSERT INTO Roles(ActorID, MovieID, Role) VALUES(actorid,movieid,role)";
	string directed = "INSERT INTO Directed(MovieID, DirectorID, Role) VALUES(“1”, “1”, “co - director”)";
	string countries ="INSERT INTO Countries(Country, MovieID) VALUES(“USA”, “1”)";
	string genres ="INSERT INTO Genres(Genre, MovieID) VALUES(“Thriller”, “1”)";
	string soundtracks ="INSERT INTO Soundtracks(Soundtrack, Composer, Performer, Year, movieID) VALUES(“The Godfather”, ”Nino Rota”, ”null”, ”1972”, “1”)";
	string ratings ="INSERT INTO Ratings(Distribution, Votes, Rank, MovieID, Year) VALUES(“00..001222”, “10039”, “1.1”, ”1”, ”1972”)";
	   
	//gebruiker
	//vraag a2
	string selector = "SELECT MAX DISTINCT(role) as maxrole FROM roles HAVING maxrole > 1";
	//vraag a3
	string selector = "SELECT actors.actor, MIN(movies.year) AS minmov, MAX(movies.year) AS maxmov, maxmo - minmov AS maxrange FROM roles, actors, movies ORDER BY maxrange LIMIT 0, 1";
	//vraag a13
	string selector = "SELECT DISINCT(movies.title) AS dismovie FROM roles, actors, movies WHERE roles.movieID = movies.movieID AND roles.actorID = actors.actorID AND actor =’Joop Braakhekke’";
	//vraag a15
	string ratingavg = "SELECT AVG(rating) AS ratingavg FROM ratings";
	string selector = "SELECT actors.actor AS actorname, COUNT(roles.actorID) AS maxbad FROM roles, actors, movies, ratings WHERE roles.movieID = movies.movieID AND roles.actorID = actors.actorID AND ratings.movieID = movies.movieID AND ratings.rating < ‘ratingavg’ ORDER BY maxbad LIMIT 0,1";
	//vraag a20
	string selector = "SELECT actors.actor AS actor, COUNT(roles.actorID) AS rolecount FROM roles,actors, movies WHERE roles.movieID = movies.movieID AND roles.actorID = actors.actorID ORDER BY rolecount LIMIT 0,3";
	//vraag b9
	string selector = "SELECT actors.actor AS actorname, COUNT(roles.actorID) AS countroles FROM roles, actors, movies, countries WHERE roles.movieID = movies.movieID AND roles.actorID = actors.actorID AND countries.movieID = movies.movieID AND country =’chosencountry’";
	//vraag b10
	string selector = "SELECT actors.actor AS actorname, COUNT(roles.actorID) AS countroles FROM roles, actors, movies WHERE roles.movieID = movies.movieID AND roles.actorID = actors.actorID";
	//vraag c4
	string selector = "SELECT actors.actor AS actorname, COUNT(roles.actorID) AS countroles, movies.year AS movieyear FROM roles, actors, movies WHERE roles.movieID = movies.movieID AND roles.actorID = actors.actorID AND actors.gender =’1’";
	//vraag c1
	string selector = "";
	//vraag
	//string selector = "";
	//vraag
	//string selector = "";


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MOVIEBOT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOVIEBOT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOVIEBOT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MOVIEBOT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
