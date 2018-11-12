// # Daniel Avalos, 2018
// # Lab 6 - Array Sorting
// Prompt user for Artist and Titles, to create a playlist
// Playlist is stored in an Array, and sorted with either Bubble or Selection Sort
// (This instance runs both, with the second running on a cloned song list, and a
//   time comparison shown afterwards)
// Once sorted, displays playlist in a self sizing table
// ( C++17 )

#include <iostream>     // ::cout, cin,
#include <iomanip>      // ::stringstream, width, left
#include <chrono>       // ::high_resolution_clock, time_point, now, duration_cast
using namespace std;

class Playlist{
private:

    static const int DEFLEN = 10,       // See Vector for adj lengths
                     DEFWID = 2;        // Artist, Title
    string songList[DEFLEN][DEFWID],         // Default songList
           songListCloned[DEFLEN][DEFWID];   // Clone list to use if comparing both sorting algos
    // bool songsEntered = false;
    // Since getting songs can cross multiple functions, common storage for buffer and prompts
    // Prevents a new declaration while enabling flexible for loops
    string getSongBuffer;    // To be parsed by getline()
    const string getSongPrompt[2] = {" artist: ", " title: "};

    // # # # Sorting Algos
    bool autoSorting = false,           // Indicates whether to sort list once songs added (All or by ndx)
         comparingBothSorts = false;    // Runs and timestamps both sorting methods, for comparison
    void BubbleSort() {
        string hold;    // acts as KingCell when swapping values
        bool swapping;  // indicates to iterate continuously or not

        do {            // while (swapping);
            swapping = false;
            for (int arrSeek=0; arrSeek<(DEFLEN-1); arrSeek++) {
                if ( songList[arrSeek][0].compare(songList[arrSeek+1][0]) > 0) {
                    // Use for loop to bubble swap one at a time
                    for (int x=0; x<DEFWID; x++) {
                        hold = songList[arrSeek][x];
                        songList[arrSeek][x] = songList[arrSeek+1][x];
                        songList[arrSeek+1][x] = hold;
                    }
                    swapping = true;
                }
            }
        } while (swapping);
    }
    void SelectionSort() {
        int arrSeek,        // Seek through array
            minNdx;         // ndx of min value. Check if any subsequent entries are lesser
        string hold;        // acts as KingCell when swapping values

        for (arrSeek=0; arrSeek<(DEFLEN-1); arrSeek++) {
            minNdx = arrSeek;
            // Seek from arrSeek+1 to endOfArr, identify lesser val and store its ndx
            for (int minSeek=arrSeek+1; minSeek<DEFLEN; minSeek++) {
                if (songListCloned[minSeek][0].compare(songListCloned[arrSeek][0]) < 0) {
                    minNdx = minSeek;
                }
            }
            // If a lesser value was found, swap with arrSeek'd val
            if (minNdx != arrSeek) {
                for (int x=0; x<DEFWID; x++) {
                    hold = songListCloned[arrSeek][x];
                    songListCloned[arrSeek][x] = songListCloned[minNdx][x];
                    songListCloned[minNdx][x] = hold;
                }
            }
        }
    }

    // # If comparingBothSorts, Song list is cloned. SelectionSort uses cloned list
    void cloneSongList() {
        for (int listSeek=0; listSeek<2; listSeek++){
            for (int nestSeek=0; nestSeek<DEFWID; nestSeek++) {
                songListCloned[listSeek][nestSeek] = songList[listSeek][nestSeek];
            }
        }
    }

    // # Tabler, creates and displays table to CLI
    // # Private Table Setters, used by displayPlayList
    unsigned long tWidth, lColWidth = 10, rColWidth = 10;

    // Determine necessary col widths and total width, based off entry lengths
    void tableSetWidths() {
        unsigned long currentArtist = 0, currentSong = 0;
                      //longestArtist = 0, longestSong = 0;
        for (auto &x : songList) {
            currentArtist = x[0].length() + 4;  // +4 to ensure col gap
            currentSong = x[1].length() + 1;    // +1 to ensure col gap
            if (currentArtist > lColWidth) { lColWidth = currentArtist;}
            if (currentSong > rColWidth) {rColWidth= currentSong;}
        }
        if (lColWidth%2 != 0) { lColWidth++; }       // Keep Col widths Even
        if (rColWidth%2 != 0) { rColWidth++; }       // Keep Col widths Even
        tWidth = lColWidth + rColWidth;
        //if (tWidth%2 != 0) { tWidth++; }    // Ensures table width is odd
    }

    // Uses Table width to create an appropriate sized header, with left and right "|" bounds
    // (if Width is 16, then returns |====Playlist====|)
    string tableHeader() {
        unsigned long fill = ((tWidth - 8) / 2);   // Centers the title relative to tWidth
        string header = "|";
        for (int x=0; x<fill; x++) {
            header += "=";
        }
        header +="Playlist";
        for (int x=0; x<=fill; x++) {
            header += "=";
        }
        header += "|";
        return header;
    }

    string tableFullLine(const char &lineChar) {
        string fullLine;
        fullLine += "|";
        for (int x=0; x<=tWidth; x++) {
            fullLine += lineChar;
        }
        fullLine += "|";
        return fullLine;
    };

    // Creates a column set line for two entries, using a stringstream buffer to manage cout,width commands
    string tableColWriter(const string &lColEntry, const string &rColEntry) {
        stringstream buffer;
        buffer << "|";
        buffer.width(lColWidth); buffer << left << lColEntry << " ";
        buffer.width(rColWidth); buffer << left << rColEntry;
        buffer << "|";
        return buffer.str();
    }

    // # Timer, used to track time needed to sort songList
    typedef chrono::high_resolution_clock Clock; // Timer Variables
    Clock::time_point timePointStart, timePointStop;
    long timePointElapsed = 0;
    void timerStart() {
        timePointStart = Clock::now();
    }
    void timerStop() {
        timePointStop = Clock::now();
        timePointElapsed = chrono::duration_cast<chrono::nanoseconds>(timePointStop - timePointStart).count();
    }

public:

    // # Constructors
    Playlist() = default;;
    explicit Playlist(bool setAutoSorting, bool setComparingBothSorts) {
        autoSorting = setAutoSorting;
        comparingBothSorts= setComparingBothSorts;
    }

    // # Setters
    // Set all songs
    void setSongListAll() {

        for (int arrNdx = 0; arrNdx<DEFLEN; arrNdx++) {
            setSongListByNdx(arrNdx);
        }
        if (autoSorting) { sortSongList(); }
        // songsEntered = true;
    }

    // Set song by single index
    void setSongListByNdx(int ndx) {
        for (int x=0; x<DEFWID ; x++) {
            getSongBuffer.clear();
            cout << "Song " << ndx+1 << getSongPrompt[x];
            getline(cin, getSongBuffer);
            songList[ndx][x] = getSongBuffer;
        }
        cout << "\n\n\n\n";
    }

    // Simple bool flag setters
    void setAutoSorting(bool enable) { comparingBothSorts = enable; }
    void setComparingBothSorts(bool enable) { comparingBothSorts = enable; }

    // # Sort calling
    // Calls sorting Algos (Always uses bubbleSort, but will run selectionSort
    //  if flagged to do so, so a time comparison can be seen)
    void sortSongList() {
        if (comparingBothSorts) {   // Track sorting times and display
            double bubbleTime,
                   selectionTime;

            timerStart();
            BubbleSort();       // Sorting Algo
            timerStop();
            bubbleTime = timePointElapsed;

            cloneSongList();    // Selection will run on cloned list for time comparison
            timerStart();
            SelectionSort();    // Sorting Algo
            timerStop();
            selectionTime = timePointElapsed;

            cout << "\nBubble Sort Time:    " << bubbleTime << " ns"
                 << "\nSelection Sort Time: " << selectionTime << " ns"
                 << "\n";
        }
        else {                  // Default to BubbleSort
            BubbleSort();
        }
    }

    // # Getters
    // Display Play List
    void displayPlayList() {
        tableSetWidths();
        cout << "\n" << tableHeader()
             << "\n" << tableColWriter("Artist", "Title")
             << "\n" << tableFullLine((char &) "-");
        for (auto &x : songList) {
            cout << "\n" << tableColWriter(x[0], x[1]);
        }
        cout << "\n" << tableFullLine((char &) "=");
    }

    // Cout << entire array. Debug
    void getSongsRaw() {
        int count = 0;
        for (auto &x : songList) {
            cout << x[0] << x[1] << "\n";
            count++;
        }
        cout << count;
    }

    // Simple flag getters
    bool getAutoSorting() { return comparingBothSorts; }
    bool getComparingBothSorts() { return comparingBothSorts; }
};

int main() {

    // Playlist instance with autoSorting disabled and comparingBothSorting enabled
    Playlist myPlaylist = Playlist(false, true);
    myPlaylist.setSongListAll();
    myPlaylist.sortSongList();
    myPlaylist.displayPlayList();

    return 0;
}
