# XDR-eXtended-Data-Recorder
XDR is a system able to evaluate people driving behaviors from a safety perspective.

## Working demo
<a href="https://gabriserra.github.io/XDR-eXtended-Data-Recorder/">Working demo</a> is hosted on Github for the client side, while it makes use of an external server. Your browser must therefore support and allow <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS">CORS</a>. Recently CORS and third-party cookies are not well seen by web browser. In order to toggle ON, it is necessary to:
### Firefox on MacOS/Windows
Enabled by default
### Google Chrome on MacOS/Windows
Enabled by default
### Safari MacOS
Preferences -> Privacy -> Prevent cross-site tracking (toggle OFF). 
### Safari iOS
Settings -> Safari -> Prevent cross-site tracking (toggle OFF).

## About 
This work has been realized in University of Pisa/Scuola Superiore Sant'Anna in the context of Industrial Application exam.

//TODO 

## Path and dependency
```
XDR-eXtended-Data-Recorder/
├──arduino
├──server
│   ├── log
|   ├── matlab_c
│   ├── sender_c
│   ├── server_c
└──web-UI
    ├── dashboard
    ├── frontend
    └── insertdata

<<<<<<< HEAD
arduino -> arduino code and external modules libraries
=======
Arduino/XDR -> arduino code and external modules libraries
MATLAB -> ..
>>>>>>> fe100541d858262ec6cd1cf6204a9e2629b3d2bd
server
    log -> raw data log that comes from the car
    matlab_c -> process the recevied data and produced the json sent to the web server
    sender_c -> launch matlab scripts and send to the web server the results in json
    server_c -> receive data from the car, save them in the log file and launches the sender
web-UI
    dashboard -> user dashboard client/server code
    frontend -> frontend page client/server code
    insertdata -> PHP endpoint to store data in external DB
```

## Video
?

## Authors
* <b>Silvio Bacci</b>
* <b>Andrea Baldecchi</b>
* <b>Gabriele Serra</b>

The same list can be found also in the <a href="https://github.com/gabriserra/XDR-eXtended-Data-Recorder/graphs/contributors">contributors of this project.</a>

## License and citation
The project comes with an Apache 2 license. Of you want to use this code, you can do without limitation but you have to document the modifications and include this license. If you want to cite, please refer to:

```
@misc {
        bacciserrabaldecchi2018,
        author = "Silvio Bacci and Andrea Baldecchi and Gabriele Serra",
        title = "XDR: A smart eXtended Data Recorder for automotive field.",
        year = 2018,
        address = "Pisa"
}
```

