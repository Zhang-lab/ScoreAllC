# ScoreAllC
ScoreAllC is a standalone c++ program for analyzing AllC.tsv files modeled to provide output in the same format as https://github.com/zhoujt1994/Luo2018_ncomm. To use, download ScoreAllC.cpp, and compile with g++ ScoreAllC.cpp -o ScoreAllC. Usage: ScoreAllC <allc.tsv> <regions.bed>.  Chromosome order must be identical in allc.tsv and regions.bed. Upon completion, ScoreAllC creates two files with header lines:

# file.allc.tsv.regions.txt

chr start end methyl_CH total_CH ratio_mCH methyl_CG total_CG ratio_mCG

...

...

...

# file.allc.tsv.regions.txt.summary.txt

sample mCCC CCC mCH CH mCG tCG mCCC_ratio mCH_ratio mCG_ratio

...

The regions file uses a bed file of regions to analyze. For convenience, a second c++ program is attached for creating a genome wide bed file (description below). For each region, the total number of CH, CG, methylCH,methylCG, and methylation ratios are reported. For the summary file, the sample-wide levels are reported along with CCC, methylCCC and ratios.

To use bin genome.cpp, complie with g++ binGenome.cpp -o binGenome. Usage: binGenome <chr names sizes> <out.bin.bed> <binsize>. This program then creates a bed-3 format file splitting the genome into bins of size <binsize>
