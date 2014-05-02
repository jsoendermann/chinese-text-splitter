#include <iostream>
#include <vector>

#include "text-splitter.hpp"

using namespace std;

int main(int argc, char **argv) {
    // Calling setlocale is necessary to make wcout work on Linux
    setlocale(LC_ALL, "");
    // Calling imbue is necessary to make wcout work on OS X
    wcout.imbue(locale(locale(), "", LC_CTYPE));
    
    TextSplitter *splitter = new TextSplitter("cedict-data.txt");

    wstring test_string = L"日本福島核災之後，法國開始反思核電，現在超過6成人支持逐步廢核。總統歐蘭德已經決定，在2025年之前，核能佔總發電產出佔比，要從目前的75％降低到50％。法國因為過去蓋太多反應爐，產能已經過剩，有時候還得在週末關掉幾間核電廠，因為不需要這麼多電，現在我們需要的不是量，而是用電彈性。此外，能源消耗成長的時代已經過去了。RTE（法國電網公司）的報告指出，法國的耗能長期不會再成長，甚至還可能衰退。核電的安全和投資金額息息相關。過去10年EDF（法國電力集團）為了節省成本，在設備維修上投資不足，價。日本福島核災之後";

    vector<wstring> output = splitter->split_string(test_string, TRAD);

    for (auto word : output) {
        wcout << word << " ";
    }
    wcout << endl;
}


