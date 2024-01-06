require HTTP::Request;
require LWP::UserAgent;
require LWP::Protocol::https;

# Parameters:
# $fileName: The name of the file to which data will be appended
# @data:     Array of data to be printed to the file
sub printTofile {                           # Subroutine to print data to a file
    my ($fileName, @data) = @_;
    open(my $OUTFILE, '>>', $fileName);     # Open the file for appending
    foreach my $r (@data) {                 # Iterate through each data item in the array
        print $OUTFILE $r."\n";             # Print each data item followed by a new line to the file
    }
    close($OUTFILE);                        # Close the file handle
}


sub getHTML {
    my ($originalURL, $outputFile) = @_;
    my $url = $originalURL;                                                     # URL to fetch HTML content from
    my $ua = LWP::UserAgent->new;                                               # Create a UserAgent object to make HTTP requests
    my $response = $ua->get($url);                                              # Send a GET request to the specified URL
    if ($response->is_success) {                                                # Check if the GET request was successful (HTTP status code 200)
        printTofile($outputFile, $response->decoded_content);                   # Corrected function name
        print "HTML content saved to $outputFile\n";                            # Print a success message to the console
    } else {
        die "failed to retrieve HTML $url: ", $response->status_line, "\n";     # If the GET request failed, print an error message to the console
    }
}


# Parameters:
# - htmlContent:
# - Maybe a limit to image file type?
# - Number of images maybe?
sub findWebImages {
    my($htmlContent) = @_;                                                              # Take in the html of a page as a parameter
    my @imgData = $htmlContent->content =~ /<(?:img|iframe).*?src="([^"]*)"[^>]*>/g;    # Regex code used to parse html of page collecting all iframe and img src text into imgData array
    printTofile("output.txt", @imgData);                                                # Print the image links to the output file
}

# Function that will organize all the important elements in HTML
# and print them to "output.txt"
# Parameters:
# - Html content
sub organizeWebInfo {
    my ($htmlContent) = @_;

    my @links = $htmlContent =~ /<a\s+[^>]*href="((?:(?!mailto:|#)[^"])+)"[^>]*>/g;
    my @imgs = $htmlContent =~ /<(?:img|iframe)[^>]*src="([^"]*)"[^>]*>/g;
    my @divs = $htmlContent =~ /<div\s+[^>]*class="([^"]*)"[^>]*>(.*?)<\/div>/g;
    # my @scripts = $htmlContent =~ /<script\s+[^>]*src="([^"]*)"[^>]*><\/script>/g;

    # Open the output file for writing
    open my $output_fh, '>', 'output.txt' or die "Cannot open output.txt: $!\n";

    # Print links to output.txt
    print $output_fh "First 10 Links:\n";
    if (@links) {
        print $output_fh "- $_\n" for @links;
    } else {
        print $output_fh "No links found.\n";
    }
    print $output_fh "\n";
    print $output_fh "\n";

    # Print images and iframes to output.txt
    print $output_fh "First 10 Images:\n";
    if (@imgs) {
        print $output_fh "- $_\n" for @imgs;
    } else {
        print $output_fh "No images or iframes found.\n";
    }
    print $output_fh "\n";
    print $output_fh "\n";

    # Print divs to output.txt
    print $output_fh "First 10 Divs:\n";
    if (@divs) {
        print $output_fh "- $_\n" for @divs;
    } else {
        print $output_fh "No divs found.\n";
    }
    print $output_fh "\n";
    print $output_fh "\n";

    # Close the output file
    close $output_fh;
}

my $url = "https://www.lego.com/en-us/themes/star-wars";
my $ua = LWP::UserAgent->new;
my $response = $ua->get($url);
my $html_content = $response->decoded_content;
organizeWebInfo($html_content);
