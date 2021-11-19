#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>


struct Fasta {
    std::string id;
    std::string seq;
};


// Parses fasta file.
// Returns vector of struct Fasta, which contains: ID, DNA sequence.
std::vector<struct Fasta> read_fasta_file(std::string path_to_fasta_file){
    std::ifstream fasta_file(path_to_fasta_file);
    std::vector<struct Fasta> vector_of_struct;
    std::string line, id, dna_sequence;

    while (std::getline(fasta_file, line)) {

        if (line.empty())
            continue;

        if (line[0] == '>') {
            if (!id.empty()) {
                //std::cout << id << " : " << dna_sequence << std::endl;
                Fasta fasta{ id, dna_sequence };
                vector_of_struct.push_back(fasta);
            }
            id = line.substr(1);
            dna_sequence.clear();
        }
        else {
            dna_sequence += line;
        }
    }
    if (!id.empty()) {
        //std::cout << id << " : " << dna_sequence << std::endl;
        Fasta fasta{ id, dna_sequence };
        vector_of_struct.push_back(fasta);
    }
    fasta_file.close();
    return vector_of_struct;
}

// Finds proteins in DNA sequences from fasta file with length >= min_length.
void find_proteins(std::string path_to_fasta_file, std::vector<std::string> vector_of_start_codons, std::vector<std::string> vector_of_stop_codons, int min_prot_len) {
    std::vector<struct Fasta> vector_of_struct = read_fasta_file(path_to_fasta_file);
    std::string dna_sequence, cur_codon;
    int start_index, stop_index, nucl_len, count = 0;

    std::cout << "List of a potential proteins with length >= " << min_prot_len << ":" << std::endl;
    for (int k = 0; k < vector_of_struct.size(); ++k) {
        dna_sequence = vector_of_struct[k].seq;

        for (int i = 0; i < dna_sequence.length(); ++i) {
            cur_codon = dna_sequence.substr(i, 3);
            if (cur_codon == vector_of_start_codons[0]) {
                start_index = i;
                for (int j = i + 3; j <= dna_sequence.length(); j += 3) {
                    cur_codon = dna_sequence.substr(j, 3);
                    if (cur_codon == vector_of_stop_codons[0] || cur_codon == vector_of_stop_codons[1] || cur_codon == vector_of_stop_codons[2]) {
                        stop_index = j + 2;
                        nucl_len = stop_index - start_index + 1;
                        if (nucl_len % 3 == 0 && nucl_len / 3 >= min_prot_len) {
                            std::cout << dna_sequence.substr(start_index, nucl_len) << std::endl;
                            count++;
                        }
                        break;
                    }
                }
            }
        }
        std::cout << "Number of a potential proteins with length >= " << min_prot_len << ":" << count << std::endl;
    }
}


int main(int argc, char* argv[]) {
    std::string path_to_fasta_file;
    int min_len;

    if (argc < 2) {
        std::cout << "Path to the file is not given" << std::endl;
        assert(argc >= 2);
    }
    else if (argc == 2) {
        path_to_fasta_file = argv[1];
        min_len = 2;
        std::cout << "Minimum length of proteins is not specified so it is set to 2" << std::endl;
    }
    else {
        path_to_fasta_file = argv[1];
        min_len = std::stoi(argv[2]);
    }

    std::vector<std::string> vector_of_start_codons = { "ATG" };
    std::vector<std::string> vector_of_stop_codons = { "TAA", "TAG", "TGA" };

    find_proteins(path_to_fasta_file, vector_of_start_codons, vector_of_stop_codons, min_len);

    return 0;
}
