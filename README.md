# XDR-eXtended-Data-Recorder
XDR is a system able to evaluate people driving behaviors from a safety perspective.

## Working demo
<a href="https://gabriserra.github.io/XDR-eXtended-Data-Recorder/">Working demo</a> is hosted on Github for the client side, while it makes use of an external server. Your browser must therefore support and allow <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS">CORS</a>.

## About 
This work has been realized in University of Pisa/Scuola Superiore Sant'Anna in the context of Industrial Application exam.

//TODO

## Path and dependency
```
XDR-eXtended-Data-Recorder/
├──Arduino
├──MATLAB
│   ├── TO BE ORGANIZED
├──server
│   ├── log
│   ├── sender_c
│   ├── server_c
└──web-UI
    ├── dashboard
    ├── frontend
    └── insertdata

Arduino/XDR -> arduino code and external modules libraries
MATLAB -> ..
server
    log -> raw data log that comes from the car
    sender_c -> receive data from the car?
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

