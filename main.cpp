#include <iostream>
#include <fstream>
#include <vector>

#include "trie.hpp"

using namespace std;

int main(int argc, char **argv) {
    // Calling setlocale is necessary to make wcout work on Linux
    setlocale(LC_ALL,"");
    // Calling imbue is necessary to make wcout work on OS X
    wcout.imbue(locale(locale(),"",LC_CTYPE));
    
    wifstream cedict_file;
    cedict_file.open("cedict-data.txt");
    // Calling imbue on the file handle is necessary to make reading
    // utf-8 files work on OS X
    cedict_file.imbue(locale(locale(),"",LC_CTYPE));
    
    vector<wstring> trad_words, simp_words;

    if (cedict_file.is_open()) {
        wstring line, trad, simp;
        while(getline(cedict_file, line)) {
            if (line.at(0) != L'#') {
                size_t first_space_index = line.find(L' ');
                size_t second_space_index = line.find(L' ', first_space_index + 1);

                trad = line.substr(0, first_space_index);
                simp = line.substr(first_space_index + 1, second_space_index - first_space_index);

                trad_words.push_back(trad);
                simp_words.push_back(simp);
            }
        }
    }
    cedict_file.close();

    
    Trie *trad_trie = new Trie();
    trad_trie->add_words(trad_words);

    wcout << trad_trie->to_string() << endl;

    cout << "Done!" << "\n";

    wstring test_string = L"日本福島核災之後，法國開始反思核電，現在超過6成人支持逐步廢核。總統歐蘭德已經決定，在2025年之前，核能佔總發電產出佔比，要從目前的75％降低到50％。法國因為過去蓋太多反應爐，產能已經過剩，有時候還得在週末關掉幾間核電廠，因為不需要這麼多電，現在我們需要的不是量，而是用電彈性。此外，能源消耗成長的時代已經過去了。RTE（法國電網公司）的報告指出，法國的耗能長期不會再成長，甚至還可能衰退。核電的安全和投資金額息息相關。過去10年EDF（法國電力集團）為了節省成本，在設備維修上投資不足，價。日本福島核災之後";

    //replace_all(test_string, " ", "  "); 
    
    /*vector<wstring> testvec;

    testvec.push_back(L"你好");
    testvec.push_back(L"你錯");
    testvec.push_back(L"我");

    Trie *trad_trie = new Trie();
    trad_trie->add_words(testvec);

    wcout << trad_trie->to_string() << endl;

    wstring test_string = L"你好我你你錯";

    wstring output = trad_trie->feed_string(test_string);

    wcout << output << endl;*/

    auto output = trad_trie->feed_string(test_string);

    //trim(output);

    for (auto word : output) {
        wcout << word << " ";
    }
    wcout << endl;
}


