import urllib, calendar, os

os.chdir("/home/takuya/bbt/goes")


cal = calendar.Calendar()

yearstart = 2010
yearend = 2011


for i in range(yearstart,yearend):
    os.mkdir(str(i))
    for j in range(1,13):
        dirname = str(i)+"/"+str(j).zfill(2)
        os.mkdir(dirname)
        for k in cal.itermonthdays(i,j):
            if k==0: continue
            date = str(i)+str(j).zfill(2)+str(k).zfill(2)
                                    
            for l in ["14", "15"]:
            url = "http://satdat.ngdc.noaa.gov/sem/goes/data/new_full/"+str(i)+"/"+str(j).zfill(2)+"/goes"+l+"/csv/g"+l+"_xrs_2s_"+date+"_"+date+".csv"

            csv = urllib.urlopen(url)
                                                                                                                                          
            if csv.getcode() == 200 :
                fname = str(i)+"/"+str(j).zfill(2)+"/"+str(k).zfill(2)+".csv"
                fp = open(fname, "w")
                fp.write(csv.read())
                fp.close()
                print fname, url

