//
// dinos.cpp

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;        // max number of rows in a valley
const int MAXCOLS = 40;        // max number of columns in a valley
const int MAXDINOSAURS = 170;  // max number of dinosaurs allowed

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Valley;  // This is needed to let the compiler know that Valley is a
// type name, since it's mentioned in the Dinosaur declaration.

class Dinosaur
{
public:
    // Constructor
    Dinosaur(Valley* vp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Valley* m_valley;
    int     m_row;
    int     m_col;
};

class Player
{
public:
    // Constructor
    Player(Valley *vp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    
private:
    Valley* m_valley;
    int     m_row;
    int     m_col;
    int     m_age;
    bool    m_dead;
};

class Valley
{
public:
    // Constructor/destructor
    Valley(int nRows, int nCols);
    ~Valley();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     dinosaurCount() const;
    int     numDinosaursAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    bool    addDinosaur(int r, int c);
    bool    addPlayer(int r, int c);
    bool    destroyDinosaur(int r, int c);
    bool    moveDinosaurs();
    
private:
    int        m_rows;
    int        m_cols;
    Player*    m_player;
    Dinosaur*  m_dinos[MAXDINOSAURS];
    int        m_nDinos;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nDinos);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Valley* m_valley;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Dinosaur implementation
///////////////////////////////////////////////////////////////////////////

Dinosaur::Dinosaur(Valley* vp, int r, int c)
{
    if (vp == nullptr)
    {
        cout << "***** A dinosaur must be created in some Valley!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > vp->rows()  ||  c < 1  ||  c > vp->cols())
    {
        cout << "***** Dinosaur created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_valley = vp;
    m_row = r;
    m_col = c;
}

int Dinosaur::row() const
{
    return m_row;
}

int Dinosaur::col() const
{
    return m_col;
}

void Dinosaur::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (randInt(0, NUMDIRS-1))
    {
        case UP:     if (m_row > 1)                m_row--; break;
        case DOWN:   if (m_row < m_valley->rows()) m_row++; break;
        case LEFT:   if (m_col > 1)                m_col--; break;
        case RIGHT:  if (m_col < m_valley->cols()) m_col++; break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Valley* vp, int r, int c)
{
    if (vp == nullptr)
    {
        cout << "***** The player must be created in some Valley!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > vp->rows()  ||  c < 1  ||  c > vp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_valley = vp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
        case UP:     if (m_row > 1)                m_row--; break;
        case DOWN:   if (m_row < m_valley->rows()) m_row++; break;
        case LEFT:   if (m_col > 1)                m_col--; break;
        case RIGHT:  if (m_col < m_valley->cols()) m_col++; break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;
    
    if (randInt(1, 3) > 1)  // miss with 2/3 probability
        return false;
    
    // determine row and column delta for the direction
    int rDelta = 0;
    int cDelta = 0;
    switch (dir)
    {
        case UP:     rDelta = -1; break;
        case DOWN:   rDelta = +1; break;
        case LEFT:   cDelta = -1; break;
        case RIGHT:  cDelta = +1; break;
        default:     return false;  // Bad direction!
    }
    
    // check along the direction until we find a dinosaur
    // or encounter the edge
    int r = row();
    int c = col();
    do
    {
        if (m_valley->numDinosaursAt(r, c) > 0)
        {
            m_valley->destroyDinosaur(r, c);  // The shot knocks out one dinosaur.
            return true;
        }
        r += rDelta;
        c += cDelta;
    } while (r >= 1  &&  r <= m_valley->rows()  &&
             c >= 1  &&  c <= m_valley->cols());
    return false;
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Valley implementations
///////////////////////////////////////////////////////////////////////////

Valley::Valley(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Valley created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nDinos = 0;
}

Valley::~Valley()
{
    for (int k = 0; k < m_nDinos; k++)
        delete m_dinos[k];
    delete m_player;
}

int Valley::rows() const
{
    return m_rows;
}

int Valley::cols() const
{
    return m_cols;
}

Player* Valley::player() const
{
    return m_player;
}

int Valley::dinosaurCount() const
{
    return m_nDinos;
}

int Valley::numDinosaursAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nDinos; k++)
    {
        const Dinosaur* dp = m_dinos[k];
        if (dp->row() == r  &&  dp->col() == c)
            count++;
    }
    return count;
}

void Valley::display(string msg) const
{
    // Position (row,col) in the valley coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each dinosaur's position
    for (int k = 0; k < m_nDinos; k++)
    {
        const Dinosaur* dp = m_dinos[k];
        char& gridChar = grid[dp->row()-1][dp->col()-1];
        switch (gridChar)
        {
            case '.':  gridChar = 'D'; break;
            case 'D':  gridChar = '2'; break;
            case '9':  break;
            default:   gridChar++; break;  // '2' through '8'
        }
    }
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a dinosaur there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, dinosaur, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << dinosaurCount() << " dinosaurs remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Valley::addDinosaur(int r, int c)
{
    // Dynamically allocate a new Dinosaur and add it to the valley
    if (m_nDinos == MAXDINOSAURS)
        return false;
    m_dinos[m_nDinos] = new Dinosaur(this, r, c);
    m_nDinos++;
    return true;
}

bool Valley::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate a new Player and add it to the valley
    m_player = new Player(this, r, c);
    return true;
}

bool Valley::destroyDinosaur(int r, int c)
{
    for (int k = 0; k < m_nDinos; k++)
    {
        if (m_dinos[k]->row() == r  &&  m_dinos[k]->col() == c)
        {
            delete m_dinos[k];
            m_dinos[k] = m_dinos[m_nDinos-1];
            m_nDinos--;
            return true;
        }
    }
    return false;
}

bool Valley::moveDinosaurs()
{
    for (int k = 0; k < m_nDinos; k++)
    {
        Dinosaur* dp = m_dinos[k];
        dp->move();
        if (dp->row() == m_player->row()  &&  dp->col() == m_player->col())
            m_player->setDead();
    }
    
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nDinos)
{
    if (nDinos < 0)
    {
        cout << "***** Cannot create Game with negative number of Dinosaurs!" << endl;
        exit(1);
    }
    if (nDinos > MAXDINOSAURS)
    {
        cout << "***** Trying to create Game with " << nDinos
        << " dinosaurs; only " << MAXDINOSAURS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nDinos > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the Dinosaurs!" << endl;
        exit(1);
    }
    
    // Create valley
    m_valley = new Valley(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_valley->addPlayer(rPlayer, cPlayer);
    
    // Populate with dinosaurs
    while (nDinos > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a dinosaur where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_valley->addDinosaur(r, c);
        nDinos--;
    }
}

Game::~Game()
{
    delete m_valley;
}

void Game::play()
{
    string msg = "";
    m_valley->display(msg);
    Player* player = m_valley->player();
    if (player == nullptr)
        return;
    
    while ( ! m_valley->player()->isDead()  &&  m_valley->dinosaurCount() > 0)
    {
        cout << "Move (u/d/l/r/su/sd/sl/sr/q or nothing): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            player->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    player->move(decodeDirection(action[0]));
                    break;
                case 's':
                    if (action.size() < 2)  // if no direction, nobody moves
                    {
                        cout << '\a' << endl;  // beep
                        continue;
                    }
                    switch (action[1])
                {
                    default:   // if bad direction, nobody moves
                        cout << '\a' << endl;  // beep
                        continue;
                    case 'u':
                    case 'd':
                    case 'l':
                    case 'r':
                        if (player->shoot(decodeDirection(action[1])))
                            msg = "Hit!";
                        else
                            msg = "Missed!";
                        break;
                }
                    break;
            }
        }
        if ( ! player->isDead())
            m_valley->moveDinosaurs();
        m_valley->display(msg);
        msg = "";
    }
    if (m_valley->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 100);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
