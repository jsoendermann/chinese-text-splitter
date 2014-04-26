#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "trie.hpp"

using namespace std;
using namespace boost::algorithm;

int main(int argc, char **argv) {
    string line;
    string trad, simp;
    ifstream cedict_file;
    vector<string> trad_words, simp_words;

    cedict_file.open("cedict-data.txt");

    if (cedict_file.is_open()) {
        while(getline(cedict_file, line)) {
            if (line.at(0) != '#') {
                size_t first_space_index = line.find(' ');
                size_t second_space_index = line.find(' ', first_space_index + 1);

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

    cout << "Done!" << "\n";

    string test_string = u8"\"日本福島\"核災之後，法國開始反思核電，現在超過6成人支持逐步廢核。總統歐蘭德已經決定，在2025年之前，核能佔總發電產出佔比，要從目前的75％降低到50％。法國因為過去蓋太多反應爐，產能已經過剩，有時候還得在週末關掉幾間核電廠，因為不需要這麼多電，現在我們需要的不是量，而是用電彈性。此外，能源消耗成長的時代已經過去了。RTE（法國電網公司）的報告指出，法國的耗能長期不會再成長，甚至還可能衰退。核電的安全和投資金額息息相關。過去10年EDF（法國電力集團）為了節省成本，在設備維修上投資不足，價。日本福島核災之後，法國開始反思核電，現在超過6成人支持逐步廢核。總統歐蘭德已經決定，在2025年之前，核能佔總發電產出佔比，要從目前的75％降低到50％。法國因為過去蓋太多反應爐，產能已經過剩，有時候還得在週末關掉幾間核電廠，因為不需要這麼多電，現在我們需要的不是量，而是用電彈性。此外，能源消耗成長的時代已經過去了。RTE（法國電網公司）的報告指出，法國的耗能長期不會再成長，甚至還可能衰退。核電的安全和投資金額息息相關。過去10年EDF（法國電力集團）為了節省成本，在設025年電廠會跟美國一樣，因為不敷成本而提早關閉。科技通常有個學習曲線，隨著時間系統建置成本會愈來愈低，太陽光電、風電皆是如此。例如德國太陽能發電，每千瓦的建置成本在7年內降低了75％。但核能卻反其道而行，愈來愈貴。幾個原因：安全維護的成本隨著時間增加，以及環境運動者的反彈聲浪，大幅拖慢核電廠興建進度，其他還包括技術人員不足，或是基礎原物料，例如銅的價格大幅上漲，讓核電成本幾乎倍增。我其實很擔心EDF被高昂的維修成本壓垮而破產，因為他們已經負債350億歐元，如果要提升所有反應爐安全標準，一定得大幅漲電價。";

    //replace_all(test_string, " ", "  "); 

    string output = trad_trie->feed_string(test_string);

    trim(output);

    cout << output << '\n';
}


