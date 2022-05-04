#!/bin/bash

./test_data_generator --mode=0 --table=TBL_MRSFileInfo_20220209121212 \
--nodeid=1 --realm=2222 --rectype=2 --begindate="2022-02-07 12:12:12" --enddate="2022-02-08 12:12:12" --caller=5001 --callee=5002 --encflag=1 --filepath=/mrs/2021 --recnum=3 \
--outfile=data.sql

./test_data_generator --mode=4 --table=TBL_MRSFileInfo_20220209121212 --tabstatus=1 --begindate="2022-02-07 12:12:12" --enddate="2022-02-28 12:12:12" --appfile=data.sql