cd ~/Build
rm -r Patwin
mkdir Patwin
cd Patwin

cmake ~/Dropbox/Patwin -DBOOST_ROOT="/home/denis/Devel/boost_1_53_0/"

cp ~/Dropbox/Patwin/install/config.xml ~/Build/Patwin/config.xml
mkdir htdocs
cp ~/Dropbox/Patwin/install/htdocs/* -R  ~/Build/Patwin/htdocs/

make
