#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"

char *outfile = "a.pl"; // generate a file for the perl code output

// Our header
void addPerlHeader(FILE** cpp) {
    fprintf(*cpp, "require HTTP::Request; \n require LWP::UserAgent;\n require LWP::Protocol::https;\n sub printTofile { \n my ($fileName, @data) = @_; \n open(my $OUTFILE, '>>', $fileName); \n foreach my $r (@data) { \n print $OUTFILE $r.\"\n\"; \n } \n close($OUTFILE); \n } \n ");
    // add helper function
}


void addPerlProgram(FILE** cpp) { // 
    for (int i=0; i<cmds; i++) {
        switch(program[i].code) {  // print out perl program with variable
            case Func1: fprintf(*cpp, "#get HTML \n my $url = \"%s\"; \n my $output_file = \"output.txt\"; \n my $response = $ua->get($url); \n if ($response->is_success) { \n open my $output_fh, '>', $output_file or die \"cannot open $output_file: $!\n\"; \n print $output_fh $response->decoded_content; \n close $output_fh; \n print \"HTML content saved $output_file\n\"; \n } else { \n die \"failed to retrieve HTML $url: \", $response->status_line, \"\n\"; \n }", program[i].data); break; 
            case Func2: fprintf(*cpp, "#find web images \n sub findWebImages { \n my($htmlContent) = @_; \n my @imgData = $htmlContent->content =~ /<(?:img|iframe).*?src=\"([^\"]*)\"[^>]*>/g; \n printTofile(\"output.txt\", @imgData);\n } ", program[i].data); break;
            case Func3: fprintf(*cpp, "#organize data \n sub organizeWebInfo { \n my ($htmlContent) = @_; \n     my @links = $htmlContent =~ /<a\\s+[^>]*href=\"((?:(?!mailto:|#)[^\"])+)\"[^>]*>/g; \n my @imgs = $htmlContent =~ /<(?:img|iframe)[^>]*src=\"([^\"]*)\"[^>]*>/g; \n my @divs = $htmlContent =~ /<div\\s+[^>]*class=\"([^\"]*)\"[^>]*>(.*?)<\\/div>/g; \n     open my $output_fh, '>', 'output.txt' or die \"Cannot open output.txt: $!\n\"; \n print $output_fh \"First 10 Links:\n\"; \n if (@links) { \n print $output_fh \"- $_\n\" for @links; \n } else { \n print $output_fh \"No links found.\n\"; \n } print $output_fh \"\n\"; \n print $output_fh \"\n\"; \nprint $output_fh \"First 10 Images:\n\"; \n if (@imgs) { \n print $output_fh \"- $_\n\" for @imgs; \n } else { \n print $output_fh \"No images or iframes found.\n\"; \n } \n print $output_fh \"\n\"; \n print $output_fh \"\n\"; \n print $output_fh \"First 10 Divs:\n\"; \n if (@divs) { \n print $output_fh \"- $_\n\" for @divs; \n } else { \n print $output_fh \"No divs found.\n\"; \n } \n print $output_fh \"\n\"; \n print $output_fh \"\n\"; \n close $output_fh; \n } " , program[i].data); break;
            // assign case? 
            case Assign: fprintf(*cpp, " $%s = \"%s\"   ;\n", program[i].data, program[i].data2); break; // $idstring = 
            default: printf("Unknown command: %d", program[i].code); break;
        }
    }
}

//compile perl instead of cpp
void compilePerl() {
    FILE* cpp = fopen(outfile, "w"); 
    addPerlHeader(&cpp);
    addPerlProgram(&cpp);
    fclose(cpp);
}

