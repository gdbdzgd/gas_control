const char CSS_STYLE[] PROGMEM = R"=====(
.container{position:relative;width:79%;margin:20px;box-sizing:border-box}.column,.columns{width:100%;float:left}.card{margin-top:2%;border-radius:6px;box-shadow:0 4px 4px rgba(204,197,185,0.5);padding-left:20px;padding-right:20px;margin-bottom:10px;min-width:150px;color:#fff}.card-slider{padding-bottom:10px}.turquoise{background:#1abc9c;border-bottom:#16a085 3px solid}.emerald{background:#2ecc71;border-bottom:#27ae60 3px solid}.peterriver{background:#3498db;border-bottom:#2980b9 3px solid}.wetasphalt{background:#34495e;border-bottom:#2c3e50 3px solid}.sunflower{background:#f1c40f;border-bottom:#e6bb0f 3px solid}.carrot{background:#e67e22;border-bottom:#d35400 3px solid}.alizarin{background:#e74c3c;border-bottom:#c0392b 3px solid}.label{box-sizing:border-box;white-space:nowrap;border-radius:.2em;padding:.12em .4em .14em;text-align:center;color:#fff;font-weight:700;line-height:1;margin-bottom:5px;display:inline-block;white-space:nowrap;vertical-align:baseline;position:relative;top:-.15em;background-color:#999;margin-bottom:10px}.label-wrap{width:90%;white-space:pre-wrap;word-wrap:break-word}.label.color-blue{background-color:#6f9ad1}.label.color-red{background-color:#d37c7c}.label.color-green{background-color:#9bc268}.label.color-orange{background-color:#dea154}.label.color-yellow{background-color:#e9d641}.label.color-purple{background-color:#9f83d1}@media(min-width:400px){.container{width:84%}}@media(min-width:630px){.container{width:98%}.column,.columns{margin-right:2%}.column:first-child,.columns:first-child{margin-left:0}.one.column,.one.columns{width:4.66666666667%}.two.columns{width:13.3333333333%}.three.columns{width:22%}.four.columns{width:30.6666666667%}.five.columns{width:39.3333333333%}.six.columns{width:48%}.seven.columns{width:56.6666666667%}.eight.columns{width:65.3333333333%}.nine.columns{width:74.0%}.ten.columns{width:82.6666666667%}.eleven.columns{width:91.3333333333%}.twelve.columns{width:100%;margin-left:0}.one-third.column{width:30.6666666667%}.two-thirds.column{width:65.3333333333%}.one-half.column{width:48%}.offset-by-one.column,.offset-by-one.columns{margin-left:8.66666666667%}.offset-by-two.column,.offset-by-two.columns{margin-left:17.3333333333%}.offset-by-three.column,.offset-by-three.columns{margin-left:26%}.offset-by-four.column,.offset-by-four.columns{margin-left:34.6666666667%}.offset-by-five.column,.offset-by-five.columns{margin-left:43.3333333333%}.offset-by-six.column,.offset-by-six.columns{margin-left:52%}.offset-by-seven.column,.offset-by-seven.columns{margin-left:60.6666666667%}.offset-by-eight.column,.offset-by-eight.columns{margin-left:69.3333333333%}.offset-by-nine.column,.offset-by-nine.columns{margin-left:78.0%}.offset-by-ten.column,.offset-by-ten.columns{margin-left:86.6666666667%}.offset-by-eleven.column,.offset-by-eleven.columns{margin-left:95.3333333333%}.offset-by-one-third.column,.offset-by-one-third.columns{margin-left:34.6666666667%}.offset-by-two-thirds.column,.offset-by-two-thirds.columns{margin-left:69.3333333333%}.offset-by-one-half.column,.offset-by-one-half.columns{margin-left:52%}}html{font-size:62.5%}body{margin:0;font-size:1.5em;line-height:1.0;font-weight:400;font-family:'Open Sans',sans-serif;color:#222;background-color:#ecf0f1}h1,h2,h3,h4,h5,h6{margin-top:0;margin-bottom:.5rem;font-weight:300}h1{font-size:4.0rem;line-height:1.2;letter-spacing:-.1rem}h2{font-size:3.6rem;line-height:1.25;letter-spacing:-.1rem}h3{font-size:3.0rem;line-height:1.3;letter-spacing:-.1rem}h4{font-size:2.4rem;line-height:1.35;letter-spacing:-.08rem}h5{font-size:1.8rem;line-height:1.5;letter-spacing:-.05rem}h6{font-size:1.5rem;line-height:1.6;letter-spacing:0}@media(min-width:630px){h1{font-size:5.0rem}h2{font-size:4.2rem}h3{font-size:3.6rem}h4{font-size:3.0rem}h5{font-size:2.0rem}h6{font-size:1.5rem}}p{margin-top:0}a{color:#1eaedb}a:hover{color:#0fa0ce}button{display:inline-block;padding:10px;border-radius:3px;color:#fff;background-color:#999}#mainHeader{display:inline-block}#conStatus{position:inherit;font-size:.75em}button,.button{margin-bottom:1rem}.u-full-width{width:100%;box-sizing:border-box}.u-max-full-width{max-width:100%;box-sizing:border-box}.u-pull-right{float:right}.u-pull-left{float:left}.tcenter{text-align:center}hr{margin-top:.5rem;margin-bottom:1.2rem;border-width:0;border-top:1px solid #e1e1e1}.container:after,.row:after,.u-cf{content:"";display:table;clear:both}.control{background-color:#ddd;background-image:linear-gradient(hsla(0,0%,0%,.1),hsla(0,0%,100%,.1));border-radius:50%;box-shadow:inset 0 1px 1px 1px hsla(0,0%,100%,.5),0 0 1px 1px hsla(0,0%,100%,.75),0 0 1px 2px hsla(0,0%,100%,.25),0 0 1px 3px hsla(0,0%,100%,.25),0 0 1px 4px hsla(0,0%,100%,.25),0 0 1px 6px hsla(0,0%,0%,.75);height:9em;margin:3em auto;position:relative;width:9em}.control ul{height:100%;padding:0;transform:rotate(45deg)}.control li{border-radius:100% 0 0 0;box-shadow:inset -1px -1px 1px hsla(0,0%,100%,.5),0 0 1px hsla(0,0%,0%,.75);display:inline-block;height:50%;overflow:hidden;width:50%}.control ul li:nth-child(2){transform:rotate(90deg)}.control ul li:nth-child(3){transform:rotate(-90deg)}.control ul li:nth-child(4){transform:rotate(180deg)}.control ul a{height:200%;position:relative;transform:rotate(-45deg);width:200%}.control a:hover,.control a:focus{background-color:hsla(0,0%,100%,.25)}.control a{border-radius:50%;color:#333;display:block;font:bold 1em/3 sans-serif;text-align:center;text-decoration:none;text-shadow:0 1px 1px hsla(0,0%,100%,.4);transition:.15s}.control .confirm{background-color:#ddd;background-image:linear-gradient(hsla(0,0%,0%,.15),hsla(0,0%,100%,.25));box-shadow:inset 0 1px 1px 1px hsla(0,0%,100%,.5),0 0 1px 1px hsla(0,0%,100%,.25),0 0 1px 2px hsla(0,0%,100%,.25),0 0 1px 3px hsla(0,0%,100%,.25),0 0 1px 4px hsla(0,0%,100%,.25),0 0 1px 6px hsla(0,0%,0%,.85);left:50%;line-height:3;margin:-1.5em;position:absolute;top:50%;width:3em}.control .confirm:hover,.control .confirm:focus{background-color:#eee}.switch{display:inline-block !important;background-color:#bebebe;border-radius:4px;box-shadow:inset 0 0 6px rgba(0,0,0,0.3);color:#fff;cursor:pointer;display:block;font-size:14px;height:26px;margin-bottom:12px;position:relative;width:60px;-webkit-transition:background-color .2s ease-in-out;-moz-transition:background-color .2s ease-in-out;-o-transition:background-color .2s ease-in-out;-ms-transition:background-color .2s ease-in-out;transition:background-color .2s ease-in-out}.switch.checked{background-color:#76d21d}.switch input[type="checkbox"]{display:none;cursor:pointer;height:10px;left:12px;position:absolute;top:8px;width:10px}.in{position:absolute;top:8px;left:12px;-webkit-transition:left .08s ease-in-out;-moz-transition:left .08s ease-in-out;-o-transition:left .08s ease-in-out;-ms-transition:left .08s ease-in-out;transition:left .08s ease-in-out}.switch.checked div{left:38px}.switch .in:before{background:#fff;background:-moz-linear-gradient(top,#fff 0,#f0f0f0 100%);background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#fff),color-stop(100%,#f0f0f0));background:-webkit-linear-gradient(top,#fff 0,#f0f0f0 100%);background:-o-linear-gradient(top,#fff 0,#f0f0f0 100%);background:-ms-linear-gradient(top,#fff 0,#f0f0f0 100%);background:linear-gradient(to bottom,#fff 0,#f0f0f0 100%);border:1px solid #fff;border-radius:2px;box-shadow:0 0 4px rgba(0,0,0,0.3);content:'';height:18px;position:absolute;top:-5px;left:-9px;width:26px}.switch .in:after{background:#f0f0f0;background:-moz-linear-gradient(top,#f0f0f0 0,#fff 100%);background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#f0f0f0),color-stop(100%,#fff));background:-webkit-linear-gradient(top,#f0f0f0 0,#fff 100%);background:-o-linear-gradient(top,#f0f0f0 0,#fff 100%);background:-ms-linear-gradient(top,#f0f0f0 0,#fff 100%);background:linear-gradient(to bottom,#f0f0f0 0,#fff 100%);border-radius:10px;content:'';height:12px;margin:-1px 0 0 -1px;position:absolute;width:12px}.rkmd-slider{display:block;position:relative;font-size:16px;font-family:'Roboto',sans-serif}.rkmd-slider input[type="range"]{overflow:hidden;position:absolute;width:1px;height:1px;opacity:0}.rkmd-slider input[type="range"]+.slider{display:block;position:relative;width:100%;height:27px;border-radius:13px;background-color:#bebebe}@media(pointer:fine){.rkmd-slider input[type="range"]+.slider{height:4px;border-radius:0}}.rkmd-slider input[type="range"]+.slider .slider-fill{display:block;position:absolute;width:0;height:100%;user-select:none;z-index:1}.rkmd-slider input[type="range"]+.slider .slider-handle{cursor:pointer;position:absolute;top:12px;left:0;width:15px;height:15px;margin-left:-8px;border-radius:50%;transition:all .2s ease;user-select:none;z-index:2}@media(pointer:fine){.rkmd-slider input[type="range"]+.slider .slider-handle{top:-5.5px}}.rkmd-slider input[type="range"]:disabled+.slider{background-color:#b0b0b0 !important}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle{cursor:default !important;background-color:#b0b0b0 !important}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill .slider-label,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle .slider-label{display:none;background-color:#b0b0b0 !important}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill.is-active,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle.is-active{top:-5.5px;width:15px;height:15px;margin-left:-8px}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill.is-active .slider-label,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle.is-active .slider-label{display:none;border-radius:50%;transform:none}.rkmd-slider input[type="range"]:disabled+.slider .slider-handle:active{box-shadow:none !important;transform:scale(1) !important}.rkmd-slider.slider-discrete .slider .slider-handle{position:relative;z-index:1}.rkmd-slider.slider-discrete .slider .slider-handle .slider-label{position:absolute;top:-17.5px;left:4px;width:30px;height:30px;-webkit-transform-origin:50% 100%;transform-origin:50% 100%;border-radius:50%;-webkit-transform:scale(1.0) rotate(-45deg);transform:scale(1.0) rotate(-45deg);-webkit-transition:all .2s ease;transition:all .2s ease}@media(pointer:fine){.rkmd-slider.slider-discrete .slider .slider-handle .slider-label{left:-2px;-webkit-transform:scale(0.5) rotate(-45deg);transform:scale(0.5) rotate(-45deg)}}.rkmd-slider.slider-discrete .slider .slider-handle .slider-label span{position:absolute;top:7px;left:0;width:100%;color:#fff;font-size:16px;text-align:center;-webkit-transform:rotate(45deg);transform:rotate(45deg);opacity:0;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}@media(pointer:fine){.rkmd-slider.slider-discrete .slider .slider-handle .slider-label span{font-size:12px}}.rkmd-slider.slider-discrete .slider .slider-handle.is-active{top:0;margin-left:-2px;width:4px;height:4px}.rkmd-slider.slider-discrete .slider .slider-handle.is-active .slider-label{top:-15px;left:-2px;border-radius:15px 15px 15px 0;-webkit-transform:rotate(-45deg) translate(23px,-25px);transform:rotate(-45deg) translate(23px,-25px)}.rkmd-slider.slider-discrete .slider .slider-handle.is-active .slider-label span{opacity:1}.rkmd-slider.slider-discrete.slider-turquoise .slider-label{background-color:#16a085}.rkmd-slider.slider-discrete.slider-emerald .slider-label{background-color:#27ae60}.peterriver{background:#3498db;border-bottom:#2980b9 3px solid}.rkmd-slider.slider-discrete.slider-peterriver .slider-label{background-color:#2980b9}.wetasphalt{background:#34495e;border-bottom:#2c3e50 3px solid}.rkmd-slider.slider-discrete.slider-wetasphalt .slider-label{background-color:#2c3e50}.sunflower{background:#f1c40f;border-bottom:#e6bb0f 3px solid}.rkmd-slider.slider-discrete.slider-sunflower .slider-label{background-color:#e6bb0f}.carrot{background:#e67e22;border-bottom:#d35400 3px solid}.rkmd-slider.slider-discrete.slider-carrot .slider-label{background-color:#d35400}.alizarin{background:#e74c3c;border-bottom:#c0392b 3px solid}.rkmd-slider.slider-discrete.slider-alizarin .slider-label{background-color:#c0392b}
)=====";

const uint8_t CSS_STYLE_GZIP[2734] PROGMEM = { 31,139,8,0,56,43,252,91,2,255,197,90,89,143,171,202,17,254,43,228,140,70,103,172,0,105,86,27,80,164,60,230,45,82,238,227,85,30,26,104,6,52,24,28,150,235,153,99,249,191,167,23,150,222,24,123,150,171,28,159,153,49,77,85,117,45,95,85,87,55,216,89,219,12,176,106,80,119,57,181,125,53,84,109,19,119,168,134,67,245,7,74,206,85,62,148,241,62,122,76,142,176,123,174,154,216,5,167,215,36,109,95,173,190,250,85,53,207,113,218,118,57,234,44,60,114,181,179,182,30,143,141,57,253,237,47,140,217,1,224,49,41,234,22,14,113,141,138,1,147,193,46,191,48,113,214,208,158,98,247,49,153,164,116,48,175,198,62,14,231,41,74,152,183,231,24,24,254,233,149,254,116,207,41,124,114,129,111,58,209,222,116,14,129,9,236,96,151,156,96,158,99,85,44,34,157,233,55,143,116,213,115,57,13,77,243,165,237,48,180,71,172,19,25,194,215,147,138,1,185,198,106,183,93,252,80,20,5,211,209,234,235,42,39,94,153,164,113,188,87,123,24,187,255,142,109,213,163,75,10,179,151,231,174,29,155,60,126,112,96,154,69,89,178,56,133,50,60,56,33,4,135,192,240,176,5,125,139,101,94,109,116,68,29,172,115,129,215,69,89,182,119,100,94,119,15,81,8,120,222,19,26,80,215,225,224,116,2,187,231,71,135,60,85,216,163,3,72,35,158,253,140,6,216,159,74,88,15,18,187,31,5,72,97,207,60,20,8,179,247,99,131,99,121,150,38,47,156,204,7,133,204,141,194,52,5,5,207,141,221,218,181,226,196,40,220,35,215,149,89,115,47,240,129,48,49,172,171,95,176,171,26,145,121,239,103,158,226,239,12,120,145,155,242,204,53,76,81,125,209,194,54,57,151,213,128,172,254,4,51,20,55,237,185,131,39,9,142,182,139,142,51,164,98,219,193,87,134,237,147,95,14,254,157,12,232,117,176,176,114,207,77,156,161,6,135,134,195,81,82,224,212,178,206,136,194,112,15,64,82,227,52,179,74,118,237,72,152,12,48,4,243,170,63,213,240,45,174,26,74,153,214,109,246,162,83,16,7,127,168,50,88,79,19,167,176,71,132,33,81,19,152,36,152,101,59,1,214,116,117,156,53,169,24,69,145,38,49,38,119,89,100,166,41,135,35,156,194,188,26,167,14,209,219,201,25,123,138,126,139,211,14,193,23,139,92,79,252,54,157,4,219,48,242,57,50,79,29,22,17,204,29,145,180,67,185,134,50,247,246,217,62,19,41,159,59,132,26,13,109,148,102,110,120,16,105,219,14,54,207,58,21,114,4,157,192,23,137,223,80,141,209,173,33,70,81,30,250,146,190,167,177,59,213,58,201,81,113,240,176,113,255,56,162,188,130,79,107,157,193,144,62,189,238,46,246,90,113,217,248,193,127,188,170,212,161,167,167,142,14,143,106,173,157,194,56,85,188,133,32,46,170,174,31,172,172,172,234,124,33,230,7,103,70,90,60,193,213,110,27,180,200,94,191,207,181,220,183,195,229,223,30,79,50,156,91,185,218,123,182,183,252,35,20,37,14,149,68,227,18,253,138,118,236,164,113,15,216,130,244,2,3,88,38,137,68,241,125,245,42,171,72,188,211,163,63,80,35,221,8,66,81,58,205,66,137,38,12,68,241,77,165,184,96,239,219,128,216,165,200,63,184,146,252,90,163,68,228,72,238,57,163,90,49,146,174,152,106,92,172,161,172,186,124,162,221,112,25,14,8,35,235,69,58,217,48,34,14,175,1,133,72,69,125,215,22,69,143,6,43,125,179,4,44,104,70,123,1,60,7,9,27,43,199,138,18,83,59,42,202,113,246,146,170,43,7,135,37,115,99,92,148,229,134,130,0,14,115,166,126,88,100,247,124,123,195,36,14,154,166,126,88,148,228,123,91,70,173,8,54,181,163,162,156,192,21,153,57,136,153,27,227,162,128,16,108,153,196,231,131,185,49,46,201,138,182,140,226,242,198,212,15,139,146,246,7,154,84,92,72,181,102,13,27,70,29,194,77,163,234,13,15,73,217,201,75,139,130,45,179,228,36,52,223,185,119,47,146,148,140,53,223,187,121,111,0,164,252,54,183,111,169,248,186,150,195,177,190,208,214,5,119,75,40,14,93,59,120,188,166,109,254,54,145,198,32,89,239,58,54,233,45,132,198,198,6,66,227,131,87,61,118,93,192,99,85,191,197,63,255,117,66,141,241,27,108,250,159,102,143,127,99,180,118,85,49,183,77,46,105,6,213,229,55,43,64,225,92,75,199,44,93,179,244,204,210,55,203,192,44,67,126,31,1,164,94,198,14,58,172,25,175,137,7,0,22,193,153,134,107,121,167,104,239,38,53,26,112,35,71,123,29,210,243,225,254,9,83,93,75,151,227,244,236,80,195,25,108,177,122,2,171,102,82,111,139,211,231,56,93,219,215,112,106,38,5,7,202,27,92,248,56,29,84,94,29,107,64,89,67,129,53,80,89,67,153,21,108,118,48,130,203,3,106,189,232,76,223,118,53,94,10,21,251,189,137,55,16,124,2,54,20,190,94,79,2,60,174,240,50,161,201,65,16,229,233,21,198,101,75,182,81,211,40,40,32,200,208,53,29,49,122,154,139,182,21,159,119,1,14,219,5,243,187,4,79,216,65,234,155,237,235,195,17,55,114,255,68,144,108,43,117,19,92,31,112,179,247,219,0,135,177,95,55,227,85,83,226,4,25,184,156,179,247,56,231,38,69,77,123,82,88,106,228,137,3,236,209,42,198,186,102,209,224,155,139,141,13,252,104,29,225,43,207,66,46,239,97,59,17,22,218,123,94,216,78,159,126,95,238,144,210,114,225,143,0,6,182,85,186,40,155,167,107,217,241,49,99,192,147,44,163,96,153,189,207,180,3,243,37,97,114,230,125,159,241,128,28,242,185,174,45,116,12,11,60,139,105,119,237,121,254,58,90,89,113,33,4,88,129,248,199,143,101,15,54,192,180,70,73,86,35,216,97,107,135,146,73,233,218,90,183,149,200,115,62,226,213,17,62,163,152,132,21,146,189,10,6,8,150,253,84,246,53,124,2,38,120,36,255,109,103,103,174,3,196,187,100,104,39,129,42,152,157,206,78,66,170,6,215,112,3,24,196,194,249,71,22,18,236,76,192,145,200,183,247,220,125,87,115,223,229,238,123,55,238,251,55,238,135,194,253,105,246,100,170,32,209,18,216,216,195,155,105,56,14,109,178,117,254,20,17,44,79,222,55,198,250,50,23,33,130,201,57,37,65,50,224,141,94,95,180,221,49,238,90,156,66,232,201,15,114,244,188,91,57,235,234,34,186,151,8,48,136,182,64,245,178,69,44,176,238,240,178,106,161,182,116,76,58,147,136,146,162,67,14,81,226,178,202,115,212,76,70,6,224,145,55,18,107,27,55,67,201,118,105,79,238,238,162,152,23,1,209,60,153,199,211,240,88,183,152,124,13,147,115,80,153,224,28,4,151,6,65,61,119,80,102,102,209,152,140,37,92,171,188,169,16,155,220,64,209,102,184,6,42,153,166,129,27,39,230,162,102,207,148,160,184,63,90,194,194,226,65,170,41,206,235,58,55,28,116,252,155,103,112,157,136,122,164,67,71,114,148,181,29,164,102,54,184,137,98,131,203,25,229,22,82,252,29,243,5,243,143,237,4,253,170,48,249,130,247,226,199,111,170,40,129,90,82,176,127,118,223,92,65,220,255,107,5,57,224,252,98,157,42,14,46,223,145,120,115,53,177,88,71,186,64,18,166,120,49,24,7,118,20,70,184,166,157,51,95,83,230,64,200,56,92,198,55,224,248,128,16,186,218,253,185,26,178,82,187,160,27,127,169,142,167,182,27,96,51,104,90,130,20,145,143,84,243,125,241,244,123,142,24,160,206,160,39,224,216,25,228,99,123,59,190,227,200,198,174,199,223,79,109,69,33,171,162,125,234,141,136,252,57,119,67,245,100,220,37,231,231,27,117,56,36,109,15,110,166,211,151,106,176,56,84,203,150,25,182,219,27,8,246,200,194,130,219,113,72,172,99,251,235,99,12,237,7,229,247,31,162,255,0,237,28,94,59,43,81,246,162,61,161,220,135,185,235,228,51,161,81,53,167,113,248,125,120,59,161,191,255,160,76,56,154,63,254,179,192,131,214,14,41,88,203,130,134,253,203,14,65,132,48,8,16,62,224,59,115,79,70,14,107,171,230,178,77,184,10,211,132,141,220,52,240,94,225,253,88,109,80,181,247,72,234,111,19,221,34,144,253,111,228,213,31,23,182,167,62,16,243,39,167,99,55,196,41,194,11,142,248,64,70,108,197,99,106,155,92,69,177,175,76,66,104,0,252,7,144,143,65,42,209,78,96,156,188,183,48,49,33,38,85,153,8,160,95,88,14,153,236,116,184,199,195,79,128,74,222,241,67,180,202,77,19,237,180,147,124,74,193,246,115,108,56,68,159,225,83,121,102,227,245,156,180,194,241,157,57,13,140,80,247,92,249,169,31,88,159,249,9,21,143,117,234,63,127,46,89,115,216,204,21,43,152,115,192,138,150,180,33,85,79,192,13,221,8,136,176,161,202,223,137,28,102,40,139,244,247,34,135,97,68,3,30,12,169,15,32,231,134,130,237,231,216,54,145,243,62,223,123,200,209,113,74,13,59,221,101,43,8,112,151,117,44,166,45,59,1,15,249,162,129,197,84,58,93,130,129,238,229,184,60,229,21,215,75,117,5,228,86,80,178,106,10,7,90,255,110,177,9,45,127,154,37,200,22,86,4,250,52,10,47,7,242,38,96,83,211,117,185,38,95,91,114,218,50,188,145,71,2,55,102,248,171,125,167,101,220,6,127,238,11,246,202,241,134,67,206,55,182,58,152,249,228,103,90,206,226,2,199,120,119,185,91,193,105,86,95,153,20,92,239,182,210,152,254,90,69,85,215,91,38,75,174,5,9,191,145,28,123,114,152,133,106,148,13,108,141,254,133,87,160,28,189,198,206,199,149,40,97,147,215,232,34,173,242,250,26,69,193,203,30,243,204,161,8,184,152,7,107,139,198,10,217,65,113,19,105,106,185,101,20,214,245,210,196,108,91,229,126,45,104,178,169,172,218,218,88,219,219,49,139,113,120,200,225,74,190,32,64,3,44,64,62,92,251,252,113,169,2,36,204,207,179,139,193,204,81,1,199,122,184,209,216,127,179,246,203,5,125,252,252,101,91,68,113,98,103,250,231,27,99,87,189,5,51,82,122,190,108,200,42,138,3,224,189,89,244,109,102,124,115,116,182,4,75,113,210,151,0,122,228,66,8,174,95,85,35,158,28,203,245,100,68,46,15,252,117,198,62,131,53,122,114,118,91,40,153,69,227,57,179,14,13,139,101,114,146,169,171,147,190,10,223,41,79,114,224,70,147,232,236,237,165,79,244,23,252,144,103,23,51,126,60,101,227,75,172,182,218,174,34,45,7,118,62,237,86,146,237,59,106,180,20,105,179,15,109,176,51,164,51,179,123,104,52,251,59,97,33,216,24,191,189,10,124,206,213,44,203,92,157,219,38,35,200,187,123,183,12,213,208,92,191,142,3,163,63,193,173,77,243,94,89,140,193,122,138,184,188,210,181,246,129,234,89,161,106,175,112,28,189,117,76,189,118,118,139,4,101,237,166,155,16,205,104,175,14,202,3,127,82,156,153,43,57,159,184,114,3,112,167,88,169,146,3,177,90,187,75,86,114,167,87,190,84,194,63,60,147,4,89,86,11,214,29,163,171,54,193,1,57,19,93,126,129,237,88,79,96,53,232,141,154,140,184,184,129,54,45,23,243,237,146,143,145,127,167,145,44,94,51,212,222,175,169,243,245,242,170,171,228,47,181,83,96,47,186,222,37,116,122,3,246,166,72,246,254,235,151,223,122,189,67,163,117,134,219,74,81,249,95,126,151,246,14,165,214,25,110,43,69,229,127,245,13,221,59,116,90,38,184,169,18,19,255,165,215,126,239,208,135,73,191,169,12,147,253,197,23,137,239,80,103,150,127,83,33,38,253,250,63,16,229,254,23,128,47,0,0 };