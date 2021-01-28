# Übungsabgabe 03
# Sebastian Pritz
# Python Version 3.7.0
# Stundenaufwand: 8h
from multiprocessing import Pool
import urllib.request
import gzip
import os

# Creating a function to download a file using the designated URL
def job(url):
    path = 'PDB/' + url.split('/')[-1]
    if not os.path.exists(path) and not os.path.exists(path.split('.')[0] + '.pdb'):
        print("Downloading " + url.split('/')[-1] + '...')
        # Download the file using urllib
        urllib.request.urlretrieve(url, path)

        # Then unzip it.
        destFile = open(path.split('.')[0] + '.pdb', 'wb')
        with gzip.open(path, 'rb') as f:
            bindata = f.read()
        destFile.write(bindata)
        destFile.close()

        # And last but not least: remove the archive
        os.remove(path)



            

    
# Took too long for my liking so I made it use multiple threads
if __name__ == '__main__':
    ftpFile = open("ftpSourceView.txt")

    # Determine the base URL of the FTP-Server by using the first line
    baseUrl = ftpFile.readline().split()[1]
    # Skip one more line
    ftpFile.readline()

    # Create the folder for the PDB files
    path = os.getcwd() + '/PDB'
    try:
        os.mkdir(path)
    except OSError:
        print("Directory already exists.")


    # Create a set of URLs to download
    urls = set()
    for idx in range(0,1000):
        fileName = ftpFile.readline().split()[1].strip('"');
        urls.add(baseUrl + '/' + fileName)
    ftpFile.close()

    # Create a Threadpool and start the download jobs automatically
    pool = Pool()
    pool.map(job, urls)

