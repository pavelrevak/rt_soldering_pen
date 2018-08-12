<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="weller_rt">
<packages>
<package name="RT-1">
<wire x1="0" y1="4" x2="0" y2="1.75" width="0.1" layer="48"/>
<wire x1="0" y1="1.75" x2="0" y2="-1.75" width="0.1" layer="48"/>
<wire x1="0" y1="-1.75" x2="0" y2="-4" width="0.1" layer="48"/>
<wire x1="0" y1="-4" x2="-1" y2="-4" width="0.1" layer="48"/>
<wire x1="-1" y1="-4" x2="-1" y2="4" width="0.1" layer="48"/>
<wire x1="-1" y1="4" x2="0" y2="4" width="0.1" layer="48"/>
<wire x1="-1" y1="4" x2="-1" y2="4.5" width="0.1" layer="48"/>
<wire x1="-1" y1="4.5" x2="-11" y2="4.5" width="0.1" layer="48"/>
<wire x1="-11" y1="4.5" x2="-11" y2="-4.5" width="0.1" layer="48"/>
<wire x1="-11" y1="-4.5" x2="-1" y2="-4.5" width="0.1" layer="48"/>
<wire x1="-1" y1="-4.5" x2="-1" y2="-4" width="0.1" layer="48"/>
<wire x1="-11" y1="4.5" x2="-11" y2="6.25" width="0.1" layer="48"/>
<wire x1="-11" y1="-4.5" x2="-11" y2="-6.25" width="0.1" layer="48"/>
<wire x1="0" y1="1.75" x2="5.5" y2="1.75" width="0.1" layer="48"/>
<wire x1="5.5" y1="1.75" x2="5.5" y2="-1.75" width="0.1" layer="48"/>
<wire x1="5.5" y1="-1.75" x2="0" y2="-1.75" width="0.1" layer="48"/>
<wire x1="6" y1="1.75" x2="6" y2="-1.75" width="0.1" layer="48"/>
<wire x1="6" y1="-1.75" x2="8.25" y2="-1.75" width="0.1" layer="48"/>
<wire x1="8.25" y1="-1.75" x2="8.25" y2="1.75" width="0.1" layer="48"/>
<wire x1="8.25" y1="1.75" x2="6" y2="1.75" width="0.1" layer="48"/>
<wire x1="9.25" y1="-1.75" x2="10" y2="-1.75" width="0.1" layer="48"/>
<wire x1="10" y1="-1.75" x2="10.5" y2="-1.25" width="0.1" layer="48"/>
<wire x1="10.5" y1="-1.25" x2="13.5" y2="-1.75" width="0.1" layer="48"/>
<wire x1="13.5" y1="-1.75" x2="14.25" y2="-0.5" width="0.1" layer="48"/>
<wire x1="14.25" y1="-0.5" x2="14.25" y2="0.5" width="0.1" layer="48"/>
<wire x1="14.25" y1="0.5" x2="13.5" y2="1.75" width="0.1" layer="48"/>
<wire x1="13.5" y1="1.75" x2="10.5" y2="1.25" width="0.1" layer="48"/>
<wire x1="10.5" y1="1.25" x2="10" y2="1.75" width="0.1" layer="48"/>
<wire x1="10" y1="1.75" x2="9.25" y2="1.75" width="0.1" layer="48"/>
<wire x1="9.25" y1="1.75" x2="9.25" y2="-1.75" width="0.1" layer="48"/>
<wire x1="5.5" y1="1.75" x2="6" y2="1.75" width="0.1" layer="48"/>
<wire x1="5.5" y1="-1.75" x2="6" y2="-1.75" width="0.1" layer="48"/>
<wire x1="8.25" y1="1.75" x2="9.25" y2="1.75" width="0.1" layer="48"/>
<wire x1="8.25" y1="-1.75" x2="9.25" y2="-1.75" width="0.1" layer="48"/>
<wire x1="10" y1="1.5" x2="10" y2="-1.5" width="0.1" layer="48"/>
<wire x1="10.5" y1="1" x2="10.5" y2="-1" width="0.1" layer="48"/>
<wire x1="13.5" y1="1.25" x2="13.5" y2="-1.25" width="0.1" layer="48"/>
<wire x1="-11" y1="6.25" x2="-22" y2="5.75" width="0.1" layer="48"/>
<wire x1="-22" y1="-5.75" x2="-11" y2="-6.25" width="0.1" layer="48"/>
<wire x1="-22" y1="5.75" x2="-34" y2="5.75" width="0.1" layer="48"/>
<wire x1="-34" y1="-5.75" x2="-22" y2="-5.75" width="0.1" layer="48"/>
<wire x1="-34" y1="5.75" x2="-44" y2="7" width="0.1" layer="48"/>
<wire x1="-44" y1="-7" x2="-34" y2="-5.75" width="0.1" layer="48"/>
<wire x1="-44" y1="7" x2="-44" y2="5.5" width="0.1" layer="48"/>
<wire x1="-44" y1="5.5" x2="-44" y2="-5.5" width="0.1" layer="48"/>
<wire x1="-44" y1="-5.5" x2="-44" y2="-7" width="0.1" layer="48"/>
<wire x1="-44" y1="5.5" x2="-54.25" y2="1.25" width="0.1" layer="48"/>
<wire x1="-54.25" y1="-1.25" x2="-44" y2="-5.5" width="0.1" layer="48"/>
<wire x1="-54.25" y1="1.25" x2="-57" y2="1.25" width="0.1" layer="48"/>
<wire x1="-57" y1="1.25" x2="-57" y2="1" width="0.1" layer="48"/>
<wire x1="-57" y1="1" x2="-57" y2="-1" width="0.1" layer="48"/>
<wire x1="-57" y1="-1" x2="-57" y2="-1.25" width="0.1" layer="48"/>
<wire x1="-57" y1="-1.25" x2="-54.25" y2="-1.25" width="0.1" layer="48"/>
<wire x1="-54.25" y1="1" x2="-54.25" y2="-1" width="0.1" layer="48"/>
<wire x1="-57" y1="1" x2="-67.5" y2="1" width="0.1" layer="48"/>
<wire x1="-67.5" y1="1" x2="-67.5" y2="-1" width="0.1" layer="48"/>
<wire x1="-67.5" y1="-1" x2="-57" y2="-1" width="0.1" layer="48"/>
<wire x1="-67.5" y1="1.5" x2="-67.5" y2="1" width="0.1" layer="48"/>
<wire x1="-67.5" y1="-1" x2="-67.5" y2="-1.5" width="0.1" layer="48"/>
<wire x1="-67.5" y1="-1.5" x2="-80.5" y2="-1.5" width="0.1" layer="48"/>
<wire x1="-80.5" y1="-1.5" x2="-86.5" y2="0" width="0.1" layer="48"/>
<wire x1="-86.5" y1="0" x2="-80.5" y2="1.5" width="0.1" layer="48"/>
<wire x1="-80.5" y1="1.5" x2="-67.5" y2="1.5" width="0.1" layer="48"/>
<wire x1="-80.5" y1="1" x2="-80.5" y2="-1" width="0.1" layer="48"/>
<wire x1="-22" y1="5" x2="-22" y2="-5" width="0.1" layer="48"/>
<wire x1="-23.75" y1="5" x2="-23.75" y2="-5" width="0.1" layer="48"/>
<wire x1="-25.5" y1="5" x2="-25.5" y2="-5" width="0.1" layer="48"/>
<wire x1="-27.25" y1="5" x2="-27.25" y2="-5" width="0.1" layer="48"/>
<wire x1="-29" y1="5" x2="-29" y2="-5" width="0.1" layer="48"/>
<wire x1="-30.75" y1="5" x2="-30.75" y2="-5" width="0.1" layer="48"/>
<wire x1="-32.5" y1="5" x2="-32.5" y2="-5" width="0.1" layer="48"/>
<wire x1="-34.25" y1="5" x2="-34.25" y2="-5" width="0.1" layer="48"/>
<wire x1="-36" y1="5.25" x2="-36" y2="-5.25" width="0.1" layer="48"/>
<wire x1="-37.75" y1="5.5" x2="-37.75" y2="-5.5" width="0.1" layer="48"/>
<wire x1="-39.5" y1="5.75" x2="-39.5" y2="-5.75" width="0.1" layer="48"/>
<wire x1="-41.25" y1="6" x2="-41.25" y2="-6" width="0.1" layer="48"/>
</package>
</packages>
<symbols>
<symbol name="RT">
<wire x1="0" y1="2.54" x2="-11.43" y2="2.54" width="0.254" layer="94"/>
<wire x1="-11.43" y1="2.54" x2="-11.43" y2="0.508" width="0.254" layer="94"/>
<wire x1="-11.43" y1="0.508" x2="-11.43" y2="-0.508" width="0.254" layer="94"/>
<wire x1="-11.43" y1="-0.508" x2="-11.43" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-11.43" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="-27.94" y1="0" x2="-24.13" y2="1.27" width="0.254" layer="94"/>
<wire x1="-27.94" y1="0" x2="-24.13" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-24.13" y1="1.27" x2="-17.78" y2="1.27" width="0.254" layer="94"/>
<wire x1="-17.78" y1="1.27" x2="-17.78" y2="0.508" width="0.254" layer="94"/>
<wire x1="-17.78" y1="0.508" x2="-11.43" y2="0.508" width="0.254" layer="94"/>
<wire x1="-24.13" y1="-1.27" x2="-17.78" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-1.27" x2="-17.78" y2="-0.508" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-0.508" x2="-11.43" y2="-0.508" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="3.81" y1="1.27" x2="7.62" y2="1.27" width="0.254" layer="94"/>
<wire x1="7.62" y1="1.27" x2="8.89" y2="1.27" width="0.254" layer="94"/>
<wire x1="8.89" y1="1.27" x2="9.398" y2="0.762" width="0.254" layer="94"/>
<wire x1="9.398" y1="0.762" x2="10.668" y2="1.27" width="0.254" layer="94"/>
<wire x1="10.668" y1="1.27" x2="11.43" y2="0.508" width="0.254" layer="94"/>
<wire x1="11.43" y1="0.508" x2="11.43" y2="-0.508" width="0.254" layer="94"/>
<wire x1="11.43" y1="-0.508" x2="10.668" y2="-1.27" width="0.254" layer="94"/>
<wire x1="10.668" y1="-1.27" x2="9.398" y2="-0.762" width="0.254" layer="94"/>
<wire x1="9.398" y1="-0.762" x2="8.89" y2="-1.27" width="0.254" layer="94"/>
<wire x1="8.89" y1="-1.27" x2="7.62" y2="-1.27" width="0.254" layer="94"/>
<wire x1="7.62" y1="-1.27" x2="3.81" y2="-1.27" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.27" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-1.016" x2="-10.16" y2="0" width="0.254" layer="94"/>
<wire x1="-10.16" y1="0" x2="-10.16" y2="1.27" width="0.254" layer="94"/>
<wire x1="-10.16" y1="1.27" x2="-7.62" y2="1.27" width="0.254" layer="94"/>
<wire x1="-7.62" y1="1.27" x2="-7.62" y2="0" width="0.254" layer="94"/>
<wire x1="-7.62" y1="0" x2="-8.89" y2="0" width="0.254" layer="94"/>
<wire x1="-8.89" y1="0" x2="-10.16" y2="0" width="0.254" layer="94"/>
<wire x1="-6.35" y1="1.27" x2="-5.08" y2="1.27" width="0.254" layer="94"/>
<wire x1="-5.08" y1="1.27" x2="-3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="-5.08" y1="1.27" x2="-5.08" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-1.27" x2="-8.89" y2="0" width="0.254" layer="94"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.254" layer="94"/>
<wire x1="7.62" y1="1.27" x2="7.62" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-0.508" x2="-17.78" y2="0.508" width="0.254" layer="94"/>
<wire x1="-24.13" y1="-0.762" x2="-24.13" y2="0.762" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="RT-1">
<gates>
<gate name="G$1" symbol="RT" x="15.24" y="0"/>
</gates>
<devices>
<device name="" package="RT-1">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="frames">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="A4L-LOC">
<wire x1="256.54" y1="3.81" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="256.54" y1="8.89" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="256.54" y1="13.97" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="256.54" y1="19.05" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="3.81" x2="161.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="24.13" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="215.265" y1="24.13" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="246.38" y1="3.81" x2="246.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="215.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="215.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<text x="217.17" y="15.24" size="2.54" layer="94">&gt;DRAWING_NAME</text>
<text x="217.17" y="10.16" size="2.286" layer="94">&gt;LAST_DATE_TIME</text>
<text x="230.505" y="5.08" size="2.54" layer="94">&gt;SHEET</text>
<text x="216.916" y="4.953" size="2.54" layer="94">Sheet:</text>
<frame x1="0" y1="0" x2="260.35" y2="179.07" columns="6" rows="4" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A4L-LOC" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A4, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A4L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="stm32">
<packages>
<package name="UFQFPN28">
<smd name="4" x="-1.925" y="0" dx="0.65" dy="0.3" layer="1" rot="R180"/>
<smd name="18" x="1.925" y="0" dx="0.65" dy="0.3" layer="1" rot="R180"/>
<smd name="11" x="0" y="-1.925" dx="0.65" dy="0.3" layer="1" rot="R270"/>
<smd name="25" x="0" y="1.925" dx="0.65" dy="0.3" layer="1" rot="R270"/>
<smd name="24" x="0.5" y="1.925" dx="0.65" dy="0.3" layer="1" rot="R270"/>
<smd name="23" x="1" y="1.925" dx="0.65" dy="0.3" layer="1" rot="R270"/>
<smd name="26" x="-0.5" y="1.925" dx="0.65" dy="0.3" layer="1" rot="R270"/>
<smd name="27" x="-1" y="1.925" dx="0.65" dy="0.3" layer="1" rot="R270"/>
<smd name="3" x="-1.925" y="0.5" dx="0.65" dy="0.3" layer="1"/>
<smd name="2" x="-1.925" y="1" dx="0.65" dy="0.3" layer="1"/>
<smd name="5" x="-1.925" y="-0.5" dx="0.65" dy="0.3" layer="1"/>
<smd name="6" x="-1.925" y="-1" dx="0.65" dy="0.3" layer="1"/>
<smd name="10" x="-0.5" y="-1.925" dx="0.65" dy="0.3" layer="1" rot="R90"/>
<smd name="9" x="-1" y="-1.925" dx="0.65" dy="0.3" layer="1" rot="R90"/>
<smd name="12" x="0.5" y="-1.925" dx="0.65" dy="0.3" layer="1" rot="R90"/>
<smd name="13" x="1" y="-1.925" dx="0.65" dy="0.3" layer="1" rot="R90"/>
<smd name="17" x="1.925" y="-0.5" dx="0.65" dy="0.3" layer="1" rot="R180"/>
<smd name="16" x="1.925" y="-1" dx="0.65" dy="0.3" layer="1" rot="R180"/>
<smd name="19" x="1.925" y="0.5" dx="0.65" dy="0.3" layer="1" rot="R180"/>
<smd name="20" x="1.925" y="1" dx="0.65" dy="0.3" layer="1" rot="R180"/>
<smd name="1" x="-2.025" y="1.5" dx="0.45" dy="0.3" layer="1" rot="R180"/>
<smd name="28" x="-1.5" y="2.025" dx="0.45" dy="0.3" layer="1" rot="R270"/>
<smd name="22" x="1.5" y="2.025" dx="0.45" dy="0.3" layer="1" rot="R270"/>
<smd name="21" x="2.025" y="1.5" dx="0.45" dy="0.3" layer="1" rot="R180"/>
<smd name="15" x="2.025" y="-1.5" dx="0.45" dy="0.3" layer="1" rot="R180"/>
<smd name="14" x="1.5" y="-2.025" dx="0.45" dy="0.3" layer="1" rot="R270"/>
<smd name="8" x="-1.5" y="-2.025" dx="0.45" dy="0.3" layer="1" rot="R270"/>
<smd name="7" x="-2.025" y="-1.5" dx="0.45" dy="0.3" layer="1" rot="R180"/>
<wire x1="-2" y1="2" x2="2" y2="2" width="0.127" layer="51"/>
<wire x1="2" y1="2" x2="2" y2="-2" width="0.127" layer="51"/>
<wire x1="2" y1="-2" x2="-2" y2="-2" width="0.127" layer="51"/>
<wire x1="-2" y1="-2" x2="-2" y2="2" width="0.127" layer="51"/>
<text x="2.3" y="-2" size="1.27" layer="25">&gt;NAME</text>
<text x="2.3" y="0" size="1.27" layer="27">&gt;VALUE</text>
<circle x="-1.45" y="1.45" radius="0.254" width="0.127" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="STM32F031GX">
<pin name="PB0/T3C3" x="-25.4" y="22.86" length="middle"/>
<pin name="PB1/T3C4" x="-25.4" y="20.32" length="middle"/>
<pin name="VDDA" x="-25.4" y="-12.7" length="middle" direction="pwr"/>
<pin name="PB3/SCK" x="-25.4" y="17.78" length="middle"/>
<pin name="PB4/MISO" x="-25.4" y="15.24" length="middle"/>
<pin name="PB5/MOSI" x="-25.4" y="12.7" length="middle"/>
<pin name="PB6/TX/SCL" x="-25.4" y="10.16" length="middle"/>
<pin name="PB7/RX/SDA" x="-25.4" y="7.62" length="middle"/>
<pin name="VSS" x="-25.4" y="-17.78" length="middle" direction="pwr"/>
<pin name="BOOT0" x="-25.4" y="-7.62" length="middle" direction="in"/>
<pin name="NRST" x="-25.4" y="-5.08" length="middle" direction="in"/>
<pin name="PA15" x="25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="T2C1/PA0" x="25.4" y="20.32" length="middle" rot="R180"/>
<pin name="T2C2/PA1" x="25.4" y="17.78" length="middle" rot="R180"/>
<pin name="T2C3/TX/PA2" x="25.4" y="15.24" length="middle" rot="R180"/>
<pin name="T2C4/RX/PA3" x="25.4" y="12.7" length="middle" rot="R180"/>
<pin name="T14C1/NSS/PA4" x="25.4" y="10.16" length="middle" rot="R180"/>
<pin name="SCK/PA5" x="25.4" y="7.62" length="middle" rot="R180"/>
<pin name="T3C1/MISO/PA6" x="25.4" y="5.08" length="middle" rot="R180"/>
<pin name="T3C2/MOSI/PA7" x="25.4" y="2.54" length="middle" rot="R180"/>
<pin name="MCO/T1C1/PA8" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="SCL/TX/T1C2/PA9" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="SDA/RX/T1C3/PA10" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="SWDIO/PA13" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="SWCLK/PA14" x="25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="VDD" x="-25.4" y="-15.24" length="middle" direction="pwr"/>
<pin name="PF0/OSC_IN" x="-25.4" y="2.54" length="middle"/>
<pin name="PF1/OSC_OUT" x="-25.4" y="0" length="middle"/>
<wire x1="-20.32" y1="25.4" x2="20.32" y2="25.4" width="0.254" layer="94"/>
<wire x1="20.32" y1="25.4" x2="20.32" y2="-20.32" width="0.254" layer="94"/>
<wire x1="20.32" y1="-20.32" x2="-20.32" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-20.32" y1="-20.32" x2="-20.32" y2="25.4" width="0.254" layer="94"/>
<text x="-20.32" y="-22.86" size="1.778" layer="95">&gt;NAME</text>
<text x="20.32" y="-22.86" size="1.778" layer="95" align="bottom-right">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="STM32F031GX" prefix="U">
<gates>
<gate name="U" symbol="STM32F031GX" x="0" y="0"/>
</gates>
<devices>
<device name="" package="UFQFPN28">
<connects>
<connect gate="U" pin="BOOT0" pad="1"/>
<connect gate="U" pin="MCO/T1C1/PA8" pad="18"/>
<connect gate="U" pin="NRST" pad="4"/>
<connect gate="U" pin="PA15" pad="23"/>
<connect gate="U" pin="PB0/T3C3" pad="14"/>
<connect gate="U" pin="PB1/T3C4" pad="15"/>
<connect gate="U" pin="PB3/SCK" pad="24"/>
<connect gate="U" pin="PB4/MISO" pad="25"/>
<connect gate="U" pin="PB5/MOSI" pad="26"/>
<connect gate="U" pin="PB6/TX/SCL" pad="27"/>
<connect gate="U" pin="PB7/RX/SDA" pad="28"/>
<connect gate="U" pin="PF0/OSC_IN" pad="2"/>
<connect gate="U" pin="PF1/OSC_OUT" pad="3"/>
<connect gate="U" pin="SCK/PA5" pad="11"/>
<connect gate="U" pin="SCL/TX/T1C2/PA9" pad="19"/>
<connect gate="U" pin="SDA/RX/T1C3/PA10" pad="20"/>
<connect gate="U" pin="SWCLK/PA14" pad="22"/>
<connect gate="U" pin="SWDIO/PA13" pad="21"/>
<connect gate="U" pin="T14C1/NSS/PA4" pad="10"/>
<connect gate="U" pin="T2C1/PA0" pad="6"/>
<connect gate="U" pin="T2C2/PA1" pad="7"/>
<connect gate="U" pin="T2C3/TX/PA2" pad="8"/>
<connect gate="U" pin="T2C4/RX/PA3" pad="9"/>
<connect gate="U" pin="T3C1/MISO/PA6" pad="12"/>
<connect gate="U" pin="T3C2/MOSI/PA7" pad="13"/>
<connect gate="U" pin="VDD" pad="17"/>
<connect gate="U" pin="VDDA" pad="5"/>
<connect gate="U" pin="VSS" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="rlc">
<packages>
<package name="0805">
<wire x1="-1" y1="0.6" x2="-0.6" y2="0.6" width="0.127" layer="51"/>
<wire x1="-0.6" y1="0.6" x2="0.6" y2="0.6" width="0.127" layer="51"/>
<wire x1="0.6" y1="0.6" x2="1" y2="0.6" width="0.127" layer="51"/>
<wire x1="1" y1="0.6" x2="1" y2="-0.6" width="0.127" layer="51"/>
<wire x1="1" y1="-0.6" x2="0.6" y2="-0.6" width="0.127" layer="51"/>
<wire x1="0.6" y1="-0.6" x2="-0.6" y2="-0.6" width="0.127" layer="51"/>
<wire x1="-0.6" y1="-0.6" x2="-1" y2="-0.6" width="0.127" layer="51"/>
<wire x1="-1" y1="-0.6" x2="-1" y2="0.6" width="0.127" layer="51"/>
<wire x1="-0.6" y1="0.6" x2="-0.6" y2="-0.6" width="0.127" layer="51"/>
<wire x1="0.6" y1="0.6" x2="0.6" y2="-0.6" width="0.127" layer="51"/>
<smd name="1" x="-0.95" y="0" dx="1.3" dy="0.7" layer="1" rot="R90"/>
<smd name="2" x="0.95" y="0" dx="1.3" dy="0.7" layer="1" rot="R90"/>
<text x="-1" y="1.4" size="0.635" layer="25" align="top-left">&gt;NAME</text>
<text x="-1" y="-1.4" size="0.635" layer="27">&gt;VALUE</text>
</package>
<package name="1717">
<smd name="1" x="-1.524" y="0" dx="4.572" dy="1.524" layer="1" rot="R90"/>
<smd name="2" x="1.524" y="0" dx="4.572" dy="1.524" layer="1" rot="R90"/>
<wire x1="-1.397" y1="2.159" x2="-2.159" y2="1.397" width="0.127" layer="51"/>
<wire x1="-2.159" y1="1.397" x2="-2.159" y2="-1.397" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-1.397" x2="-1.397" y2="-2.159" width="0.127" layer="51"/>
<wire x1="-1.397" y1="-2.159" x2="1.397" y2="-2.159" width="0.127" layer="51"/>
<wire x1="1.397" y1="-2.159" x2="2.159" y2="-1.397" width="0.127" layer="51"/>
<wire x1="2.159" y1="-1.397" x2="2.159" y2="1.397" width="0.127" layer="51"/>
<wire x1="2.159" y1="1.397" x2="1.397" y2="2.159" width="0.127" layer="51"/>
<wire x1="1.397" y1="2.159" x2="-1.397" y2="2.159" width="0.127" layer="51"/>
<text x="-1.754" y="1.042" size="0.635" layer="25" align="top-left">&gt;NAME</text>
<text x="-1.754" y="-1.042" size="0.635" layer="27">&gt;VALUE</text>
</package>
<package name="0402">
<smd name="1" x="-0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<smd name="2" x="0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<wire x1="-0.5" y1="0.25" x2="-0.2" y2="0.25" width="0.127" layer="51"/>
<wire x1="-0.2" y1="0.25" x2="0.2" y2="0.25" width="0.127" layer="51"/>
<wire x1="0.2" y1="0.25" x2="0.5" y2="0.25" width="0.127" layer="51"/>
<wire x1="0.5" y1="0.25" x2="0.5" y2="-0.25" width="0.127" layer="51"/>
<wire x1="0.5" y1="-0.25" x2="0.2" y2="-0.25" width="0.127" layer="51"/>
<wire x1="0.2" y1="-0.25" x2="-0.2" y2="-0.25" width="0.127" layer="51"/>
<wire x1="-0.2" y1="-0.25" x2="-0.5" y2="-0.25" width="0.127" layer="51"/>
<wire x1="-0.5" y1="-0.25" x2="-0.5" y2="0.25" width="0.127" layer="51"/>
<wire x1="-0.2" y1="0.25" x2="-0.2" y2="-0.25" width="0.127" layer="51"/>
<wire x1="0.2" y1="0.25" x2="0.2" y2="-0.25" width="0.127" layer="51"/>
<text x="-0.65" y="1.05" size="0.635" layer="25" align="top-left">&gt;NAME</text>
<text x="-0.5" y="-1.05" size="0.635" layer="27">&gt;VALUE</text>
</package>
<package name="0603">
<smd name="1" x="-0.75" y="0" dx="0.9" dy="0.6" layer="1" rot="R90"/>
<smd name="2" x="0.75" y="0" dx="0.9" dy="0.6" layer="1" rot="R90"/>
<wire x1="-0.8" y1="0.4" x2="-0.5" y2="0.4" width="0.127" layer="51"/>
<wire x1="-0.5" y1="0.4" x2="0.5" y2="0.4" width="0.127" layer="51"/>
<wire x1="0.5" y1="0.4" x2="0.8" y2="0.4" width="0.127" layer="51"/>
<wire x1="0.8" y1="0.4" x2="0.8" y2="-0.4" width="0.127" layer="51"/>
<wire x1="0.8" y1="-0.4" x2="0.5" y2="-0.4" width="0.127" layer="51"/>
<wire x1="0.5" y1="-0.4" x2="-0.5" y2="-0.4" width="0.127" layer="51"/>
<wire x1="-0.5" y1="-0.4" x2="-0.8" y2="-0.4" width="0.127" layer="51"/>
<wire x1="-0.8" y1="-0.4" x2="-0.8" y2="0.4" width="0.127" layer="51"/>
<wire x1="-0.5" y1="0.4" x2="-0.5" y2="-0.4" width="0.127" layer="51"/>
<wire x1="0.5" y1="0.4" x2="0.5" y2="-0.4" width="0.127" layer="51"/>
<text x="-0.8" y="1.2" size="0.635" layer="25" align="top-left">&gt;NAME</text>
<text x="-0.8" y="-1.2" size="0.635" layer="27">&gt;VALUE</text>
</package>
<package name="1008">
<smd name="1" x="-1.1" y="0" dx="2.1" dy="1" layer="1" rot="R90"/>
<smd name="2" x="1.1" y="0" dx="2.1" dy="1" layer="1" rot="R90"/>
<wire x1="-1.25" y1="1" x2="-0.65" y2="1" width="0.127" layer="51"/>
<wire x1="-0.65" y1="1" x2="0.65" y2="1" width="0.127" layer="51"/>
<wire x1="0.65" y1="1" x2="1.25" y2="1" width="0.127" layer="51"/>
<wire x1="1.25" y1="1" x2="1.25" y2="-1" width="0.127" layer="51"/>
<wire x1="1.25" y1="-1" x2="0.65" y2="-1" width="0.127" layer="51"/>
<wire x1="0.65" y1="-1" x2="-0.65" y2="-1" width="0.127" layer="51"/>
<wire x1="-0.65" y1="-1" x2="-1.25" y2="-1" width="0.127" layer="51"/>
<wire x1="-1.25" y1="-1" x2="-1.25" y2="1" width="0.127" layer="51"/>
<wire x1="-0.65" y1="1" x2="-0.65" y2="-1" width="0.127" layer="51"/>
<wire x1="0.65" y1="1" x2="0.65" y2="-1" width="0.127" layer="51"/>
<text x="-1.3" y="1.75" size="0.635" layer="25" align="top-left">&gt;NAME</text>
<text x="-1.3" y="-1.75" size="0.635" layer="27">&gt;VALUE</text>
</package>
<package name="1206">
<smd name="1" x="-1.45" y="0" dx="1.6" dy="0.9" layer="1" rot="R90"/>
<smd name="2" x="1.45" y="0" dx="1.6" dy="0.9" layer="1" rot="R90"/>
<wire x1="-1.5" y1="0.75" x2="-1.1" y2="0.75" width="0.127" layer="51"/>
<wire x1="-1.1" y1="0.75" x2="1.1" y2="0.75" width="0.127" layer="51"/>
<wire x1="1.1" y1="0.75" x2="1.5" y2="0.75" width="0.127" layer="51"/>
<wire x1="1.5" y1="0.75" x2="1.5" y2="-0.75" width="0.127" layer="51"/>
<wire x1="1.5" y1="-0.75" x2="1.1" y2="-0.75" width="0.127" layer="51"/>
<wire x1="1.1" y1="-0.75" x2="-1.1" y2="-0.75" width="0.127" layer="51"/>
<wire x1="-1.1" y1="-0.75" x2="-1.5" y2="-0.75" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-0.75" x2="-1.5" y2="0.75" width="0.127" layer="51"/>
<wire x1="-1.1" y1="0.75" x2="-1.1" y2="-0.75" width="0.127" layer="51"/>
<wire x1="1.1" y1="0.75" x2="1.1" y2="-0.75" width="0.127" layer="51"/>
<text x="-1.5" y="1.55" size="0.635" layer="25" align="top-left">&gt;NAME</text>
<text x="-1.5" y="-1.55" size="0.635" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="R">
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<wire x1="-2.54" y1="1.016" x2="2.54" y2="1.016" width="0.254" layer="94"/>
<wire x1="2.54" y1="1.016" x2="2.54" y2="-1.016" width="0.254" layer="94"/>
<wire x1="2.54" y1="-1.016" x2="-2.54" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.016" x2="-2.54" y2="1.016" width="0.254" layer="94"/>
<text x="-2.54" y="1.27" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.54" y="-1.27" size="1.27" layer="96" align="top-left">&gt;VALUE</text>
</symbol>
<symbol name="C">
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
<pin name="2" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<wire x1="0.508" y1="1.016" x2="0.508" y2="0" width="0.508" layer="94"/>
<wire x1="0.508" y1="0" x2="0.508" y2="-1.016" width="0.508" layer="94"/>
<wire x1="-0.508" y1="-1.016" x2="-0.508" y2="0" width="0.508" layer="94"/>
<text x="-2.54" y="1.27" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.54" y="-1.27" size="1.27" layer="96" align="top-left">&gt;VALUE</text>
<wire x1="-0.508" y1="0" x2="-0.508" y2="1.016" width="0.508" layer="94"/>
<wire x1="-0.508" y1="0" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0.508" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
</symbol>
<symbol name="L">
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="-2.54" y="1.27" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.54" y="-1.27" size="1.27" layer="96" align="top-left">&gt;VALUE</text>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="-1.27" y1="0" x2="0" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="0" y1="0" x2="1.27" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.254" layer="94" curve="-180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" prefix="R" uservalue="yes">
<gates>
<gate name="R" symbol="R" x="0" y="0" swaplevel="1"/>
</gates>
<devices>
<device name="0805" package="0805">
<connects>
<connect gate="R" pin="1" pad="1"/>
<connect gate="R" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="0603">
<connects>
<connect gate="R" pin="1" pad="1"/>
<connect gate="R" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402" package="0402">
<connects>
<connect gate="R" pin="1" pad="1"/>
<connect gate="R" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="1206">
<connects>
<connect gate="R" pin="1" pad="1"/>
<connect gate="R" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="C" prefix="C" uservalue="yes">
<gates>
<gate name="C" symbol="C" x="0" y="0" swaplevel="1"/>
</gates>
<devices>
<device name="0603" package="0603">
<connects>
<connect gate="C" pin="1" pad="1"/>
<connect gate="C" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="0805">
<connects>
<connect gate="C" pin="1" pad="1"/>
<connect gate="C" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402" package="0402">
<connects>
<connect gate="C" pin="1" pad="1"/>
<connect gate="C" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="1206">
<connects>
<connect gate="C" pin="1" pad="1"/>
<connect gate="C" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="L" prefix="L" uservalue="yes">
<gates>
<gate name="L1" symbol="L" x="0" y="0"/>
</gates>
<devices>
<device name="0402" package="0402">
<connects>
<connect gate="L1" pin="1" pad="1"/>
<connect gate="L1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="0603">
<connects>
<connect gate="L1" pin="1" pad="1"/>
<connect gate="L1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="0805">
<connects>
<connect gate="L1" pin="1" pad="1"/>
<connect gate="L1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1008" package="1008">
<connects>
<connect gate="L1" pin="1" pad="1"/>
<connect gate="L1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="1206">
<connects>
<connect gate="L1" pin="1" pad="1"/>
<connect gate="L1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1717" package="1717">
<connects>
<connect gate="L1" pin="1" pad="1"/>
<connect gate="L1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="analog_devices">
<packages>
<package name="MSOP8">
<smd name="2" x="-0.325" y="-2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<smd name="1" x="-0.975" y="-2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<smd name="3" x="0.325" y="-2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<smd name="4" x="0.975" y="-2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<smd name="5" x="0.975" y="2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<smd name="6" x="0.325" y="2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<smd name="7" x="-0.325" y="2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<smd name="8" x="-0.975" y="2.1" dx="1" dy="0.35" layer="1" rot="R90"/>
<wire x1="-1.5" y1="1.5" x2="-1.075" y2="1.5" width="0.127" layer="51"/>
<wire x1="-1.075" y1="1.5" x2="-0.875" y2="1.5" width="0.127" layer="51"/>
<wire x1="-0.875" y1="1.5" x2="-0.425" y2="1.5" width="0.127" layer="51"/>
<wire x1="-0.425" y1="1.5" x2="-0.225" y2="1.5" width="0.127" layer="51"/>
<wire x1="-0.225" y1="1.5" x2="0.225" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.225" y1="1.5" x2="0.425" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.425" y1="1.5" x2="0.875" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.875" y1="1.5" x2="1.075" y2="1.5" width="0.127" layer="51"/>
<wire x1="1.075" y1="1.5" x2="1.5" y2="1.5" width="0.127" layer="51"/>
<wire x1="1.5" y1="1.5" x2="1.5" y2="-1.5" width="0.127" layer="51"/>
<wire x1="1.5" y1="-1.5" x2="1.075" y2="-1.5" width="0.127" layer="51"/>
<wire x1="1.075" y1="-1.5" x2="0.875" y2="-1.5" width="0.127" layer="51"/>
<wire x1="0.875" y1="-1.5" x2="0.425" y2="-1.5" width="0.127" layer="51"/>
<wire x1="0.425" y1="-1.5" x2="0.225" y2="-1.5" width="0.127" layer="51"/>
<wire x1="0.225" y1="-1.5" x2="-0.225" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-0.225" y1="-1.5" x2="-0.425" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-0.425" y1="-1.5" x2="-0.875" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-0.875" y1="-1.5" x2="-1.075" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-1.075" y1="-1.5" x2="-1.5" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-1.5" x2="-1.5" y2="1.5" width="0.127" layer="51"/>
<circle x="-1" y="-1" radius="0.05" width="0.127" layer="51"/>
<text x="1.75" y="-1.55" size="1.27" layer="25">&gt;NAME</text>
<text x="1.8" y="1.55" size="1.27" layer="27" align="top-left">&gt;VALUE</text>
<wire x1="-1.075" y1="1.5" x2="-1.075" y2="2" width="0.127" layer="51"/>
<wire x1="-1.075" y1="2" x2="-1.075" y2="2.4" width="0.127" layer="51"/>
<wire x1="-1.075" y1="2.4" x2="-0.875" y2="2.4" width="0.127" layer="51"/>
<wire x1="-0.875" y1="2.4" x2="-0.875" y2="2" width="0.127" layer="51"/>
<wire x1="-0.875" y1="2" x2="-0.875" y2="1.5" width="0.127" layer="51"/>
<wire x1="-0.425" y1="1.5" x2="-0.425" y2="2" width="0.127" layer="51"/>
<wire x1="-0.425" y1="2" x2="-0.425" y2="2.4" width="0.127" layer="51"/>
<wire x1="-0.425" y1="2.4" x2="-0.225" y2="2.4" width="0.127" layer="51"/>
<wire x1="-0.225" y1="2.4" x2="-0.225" y2="2" width="0.127" layer="51"/>
<wire x1="-0.225" y1="2" x2="-0.225" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.225" y1="1.5" x2="0.225" y2="2" width="0.127" layer="51"/>
<wire x1="0.225" y1="2" x2="0.225" y2="2.4" width="0.127" layer="51"/>
<wire x1="0.225" y1="2.4" x2="0.425" y2="2.4" width="0.127" layer="51"/>
<wire x1="0.425" y1="2.4" x2="0.425" y2="2" width="0.127" layer="51"/>
<wire x1="0.425" y1="2" x2="0.425" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.875" y1="1.5" x2="0.875" y2="2" width="0.127" layer="51"/>
<wire x1="0.875" y1="2" x2="0.875" y2="2.4" width="0.127" layer="51"/>
<wire x1="0.875" y1="2.4" x2="1.075" y2="2.4" width="0.127" layer="51"/>
<wire x1="1.075" y1="2.4" x2="1.075" y2="2" width="0.127" layer="51"/>
<wire x1="1.075" y1="2" x2="1.075" y2="1.5" width="0.127" layer="51"/>
<wire x1="-1.075" y1="-1.5" x2="-1.075" y2="-2" width="0.127" layer="51"/>
<wire x1="-1.075" y1="-2" x2="-1.075" y2="-2.4" width="0.127" layer="51"/>
<wire x1="-1.075" y1="-2.4" x2="-0.875" y2="-2.4" width="0.127" layer="51"/>
<wire x1="-0.875" y1="-2.4" x2="-0.875" y2="-2" width="0.127" layer="51"/>
<wire x1="-0.875" y1="-2" x2="-0.875" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-0.425" y1="-1.5" x2="-0.425" y2="-2" width="0.127" layer="51"/>
<wire x1="-0.425" y1="-2" x2="-0.425" y2="-2.425" width="0.127" layer="51"/>
<wire x1="-0.425" y1="-2.425" x2="-0.225" y2="-2.425" width="0.127" layer="51"/>
<wire x1="-0.225" y1="-2.425" x2="-0.225" y2="-2" width="0.127" layer="51"/>
<wire x1="-0.225" y1="-2" x2="-0.225" y2="-1.5" width="0.127" layer="51"/>
<wire x1="0.225" y1="-1.5" x2="0.225" y2="-2" width="0.127" layer="51"/>
<wire x1="0.225" y1="-2" x2="0.225" y2="-2.4" width="0.127" layer="51"/>
<wire x1="0.225" y1="-2.4" x2="0.425" y2="-2.4" width="0.127" layer="51"/>
<wire x1="0.425" y1="-2.4" x2="0.425" y2="-2" width="0.127" layer="51"/>
<wire x1="0.425" y1="-2" x2="0.425" y2="-1.5" width="0.127" layer="51"/>
<wire x1="0.875" y1="-1.5" x2="0.875" y2="-2" width="0.127" layer="51"/>
<wire x1="0.875" y1="-2" x2="0.875" y2="-2.4" width="0.127" layer="51"/>
<wire x1="0.875" y1="-2.4" x2="1.075" y2="-2.4" width="0.127" layer="51"/>
<wire x1="1.075" y1="-2.4" x2="1.075" y2="-2" width="0.127" layer="51"/>
<wire x1="1.075" y1="-2" x2="1.075" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-1.075" y1="-2" x2="-0.875" y2="-2" width="0.127" layer="51"/>
<wire x1="-0.425" y1="-2" x2="-0.225" y2="-2" width="0.127" layer="51"/>
<wire x1="0.225" y1="-2" x2="0.425" y2="-2" width="0.127" layer="51"/>
<wire x1="0.875" y1="-2" x2="1.075" y2="-2" width="0.127" layer="51"/>
<wire x1="-1.075" y1="2" x2="-0.875" y2="2" width="0.127" layer="51"/>
<wire x1="-0.425" y1="2" x2="-0.225" y2="2" width="0.127" layer="51"/>
<wire x1="0.225" y1="2" x2="0.425" y2="2" width="0.127" layer="51"/>
<wire x1="0.875" y1="2" x2="1.075" y2="2" width="0.127" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="OP_AMP">
<pin name="IN+" x="-10.16" y="2.54" visible="off" length="middle" direction="in"/>
<pin name="IN-" x="-10.16" y="-2.54" visible="off" length="middle" direction="in"/>
<pin name="OUT" x="10.16" y="0" visible="off" length="middle" direction="out" rot="R180"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-4.064" y2="2.54" width="0.254" layer="94"/>
<wire x1="-3.302" y1="3.302" x2="-3.302" y2="1.778" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-2.54" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<pin name="V+" x="0" y="7.62" visible="off" length="middle" direction="pwr" rot="R270"/>
<pin name="V-" x="0" y="-7.62" visible="off" length="middle" direction="pwr" rot="R90"/>
<text x="2.54" y="-2.54" size="1.27" layer="95" align="top-left">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.27" layer="96" align="top-left">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="AD8551" prefix="U">
<gates>
<gate name="IC" symbol="OP_AMP" x="0" y="0"/>
</gates>
<devices>
<device name="RM" package="MSOP8">
<connects>
<connect gate="IC" pin="IN+" pad="3"/>
<connect gate="IC" pin="IN-" pad="2"/>
<connect gate="IC" pin="OUT" pad="6"/>
<connect gate="IC" pin="V+" pad="7"/>
<connect gate="IC" pin="V-" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="jack">
<packages>
<package name="SJ-3501-SMT">
<wire x1="0" y1="2.9" x2="2" y2="2.9" width="0.1" layer="51"/>
<wire x1="2" y1="2.9" x2="3" y2="2.9" width="0.1" layer="51"/>
<wire x1="3" y1="2.9" x2="5.2" y2="2.9" width="0.1" layer="51"/>
<wire x1="5.2" y1="2.9" x2="6.2" y2="2.9" width="0.1" layer="51"/>
<wire x1="6.2" y1="2.9" x2="10.8" y2="2.9" width="0.1" layer="51"/>
<wire x1="10.8" y1="2.9" x2="12" y2="2.9" width="0.1" layer="51"/>
<wire x1="12" y1="2.9" x2="12" y2="-2.9" width="0.1" layer="51"/>
<wire x1="12" y1="-2.9" x2="10.8" y2="-2.9" width="0.1" layer="51"/>
<wire x1="10.8" y1="-2.9" x2="3" y2="-2.9" width="0.1" layer="51"/>
<wire x1="3" y1="-2.9" x2="2" y2="-2.9" width="0.1" layer="51"/>
<wire x1="2" y1="-2.9" x2="0" y2="-2.9" width="0.1" layer="51"/>
<wire x1="0" y1="-2.9" x2="0" y2="-2.5" width="0.1" layer="51"/>
<wire x1="0" y1="-2.5" x2="0" y2="2.5" width="0.1" layer="51"/>
<wire x1="0" y1="2.5" x2="0" y2="2.9" width="0.1" layer="51"/>
<wire x1="0" y1="2.5" x2="-2.5" y2="2.5" width="0.1" layer="51"/>
<wire x1="-2.5" y1="2.5" x2="-2.5" y2="-2.5" width="0.1" layer="51"/>
<wire x1="-2.5" y1="-2.5" x2="0" y2="-2.5" width="0.1" layer="51"/>
<wire x1="0" y1="3" x2="12" y2="3" width="0.1" layer="20"/>
<wire x1="12" y1="3" x2="12.4" y2="2.6" width="0.1" layer="20"/>
<wire x1="12.4" y1="2.6" x2="12.4" y2="0.7" width="0.1" layer="20"/>
<wire x1="12.4" y1="0.7" x2="12.1" y2="0.4" width="0.1" layer="20"/>
<wire x1="12.1" y1="0.4" x2="12.1" y2="-0.4" width="0.1" layer="20"/>
<wire x1="12.1" y1="-0.4" x2="12.4" y2="-0.7" width="0.1" layer="20"/>
<wire x1="12.4" y1="-0.7" x2="12.4" y2="-2.6" width="0.1" layer="20"/>
<wire x1="12.4" y1="-2.6" x2="12" y2="-3" width="0.1" layer="20"/>
<wire x1="12" y1="-3" x2="0" y2="-3" width="0.1" layer="20"/>
<wire x1="2" y1="2.9" x2="2" y2="3.9" width="0.1" layer="51"/>
<wire x1="2" y1="3.9" x2="3" y2="3.9" width="0.1" layer="51"/>
<wire x1="3" y1="3.9" x2="3" y2="2.9" width="0.1" layer="51"/>
<wire x1="2" y1="-2.9" x2="2" y2="-3.9" width="0.1" layer="51"/>
<wire x1="2" y1="-3.9" x2="3" y2="-3.9" width="0.1" layer="51"/>
<wire x1="3" y1="-3.9" x2="3" y2="-2.9" width="0.1" layer="51"/>
<wire x1="12" y1="2.9" x2="12" y2="3.9" width="0.1" layer="51"/>
<wire x1="12" y1="3.9" x2="10.8" y2="3.9" width="0.1" layer="51"/>
<wire x1="10.8" y1="3.9" x2="10.8" y2="2.9" width="0.1" layer="51"/>
<wire x1="12" y1="-2.9" x2="12" y2="-3.9" width="0.1" layer="51"/>
<wire x1="12" y1="-3.9" x2="10.8" y2="-3.9" width="0.1" layer="51"/>
<wire x1="10.8" y1="-3.9" x2="10.8" y2="-2.9" width="0.1" layer="51"/>
<wire x1="5.2" y1="2.9" x2="5.2" y2="3.9" width="0.1" layer="51"/>
<wire x1="5.2" y1="3.9" x2="6.2" y2="3.9" width="0.1" layer="51"/>
<wire x1="6.2" y1="3.9" x2="6.2" y2="2.9" width="0.1" layer="51"/>
<smd name="2" x="11.4" y="3.8" dx="1.7" dy="1" layer="1"/>
<smd name="4" x="11.4" y="-3.8" dx="1.7" dy="1" layer="1"/>
<pad name="5" x="2.5" y="3.9" drill="1.1" diameter="1.2" shape="square"/>
<pad name="3" x="5.7" y="3.9" drill="1.1" diameter="1.2" shape="square"/>
<pad name="1" x="2.5" y="-3.9" drill="1.1" diameter="1.2" shape="square" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="JACK_3P">
<pin name="1" x="5.08" y="0" visible="off" length="short" rot="R180"/>
<pin name="3" x="5.08" y="2.54" visible="off" length="short" rot="R180"/>
<pin name="2" x="5.08" y="5.08" visible="off" length="short" rot="R180"/>
<wire x1="-1.016" y1="-1.524" x2="-1.016" y2="1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.016" x2="-1.016" y2="3.556" width="0.254" layer="94"/>
<wire x1="-1.016" y1="3.556" x2="-1.016" y2="4.572" width="0.254" layer="94"/>
<wire x1="-1.016" y1="4.572" x2="-0.508" y2="5.08" width="0.254" layer="94"/>
<wire x1="-0.508" y1="5.08" x2="-1.016" y2="6.096" width="0.254" layer="94"/>
<wire x1="-1.016" y1="6.096" x2="-0.508" y2="6.604" width="0.254" layer="94"/>
<wire x1="-0.508" y1="6.604" x2="0.508" y2="6.604" width="0.254" layer="94"/>
<wire x1="0.508" y1="6.604" x2="1.016" y2="6.096" width="0.254" layer="94"/>
<wire x1="1.016" y1="6.096" x2="0.508" y2="5.08" width="0.254" layer="94"/>
<wire x1="0.508" y1="5.08" x2="1.016" y2="4.572" width="0.254" layer="94"/>
<wire x1="1.016" y1="4.572" x2="1.016" y2="3.556" width="0.254" layer="94"/>
<wire x1="1.016" y1="3.556" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.016" x2="1.016" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-2.032" y1="-1.524" x2="-1.016" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-1.524" x2="1.016" y2="-1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="-1.524" x2="2.032" y2="-1.524" width="0.254" layer="94"/>
<wire x1="2.032" y1="-1.524" x2="2.032" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.032" y1="-2.54" x2="-2.032" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.032" y1="-2.54" x2="-2.032" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.016" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="3.556" x2="1.016" y2="3.556" width="0.254" layer="94"/>
<wire x1="1.524" y1="5.08" x2="2.54" y2="5.588" width="0.254" layer="94"/>
<wire x1="2.54" y1="5.588" x2="2.54" y2="4.572" width="0.254" layer="94"/>
<wire x1="2.54" y1="4.572" x2="1.524" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="3.048" x2="2.54" y2="2.032" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.032" x2="1.524" y2="2.54" width="0.254" layer="94"/>
<wire x1="1.524" y1="2.54" x2="2.54" y2="3.048" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.508" x2="2.54" y2="-0.508" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.508" x2="1.524" y2="0" width="0.254" layer="94"/>
<wire x1="1.524" y1="0" x2="2.54" y2="0.508" width="0.254" layer="94"/>
<text x="-2.54" y="7.112" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.032" y="-4.572" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="SJ-3501-SMT">
<gates>
<gate name="CON" symbol="JACK_3P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SJ-3501-SMT">
<connects>
<connect gate="CON" pin="1" pad="1 5"/>
<connect gate="CON" pin="2" pad="2 4"/>
<connect gate="CON" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="mosfet">
<packages>
<package name="SOIC8">
<wire x1="-2.413" y1="-1.905" x2="-2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-1.905" x2="-1.651" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-1.651" y1="-1.905" x2="-0.889" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-1.905" x2="-0.381" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-0.381" y1="-1.905" x2="0.381" y2="-1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="-1.905" x2="0.889" y2="-1.905" width="0.127" layer="51"/>
<wire x1="0.889" y1="-1.905" x2="1.651" y2="-1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="-1.905" x2="2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="2.159" y1="-1.905" x2="2.413" y2="-1.905" width="0.127" layer="51"/>
<wire x1="2.413" y1="-1.905" x2="2.413" y2="-1.397" width="0.127" layer="51"/>
<wire x1="2.413" y1="-1.397" x2="2.413" y2="1.905" width="0.127" layer="51"/>
<wire x1="2.413" y1="1.905" x2="2.159" y2="1.905" width="0.127" layer="51"/>
<wire x1="2.159" y1="1.905" x2="1.651" y2="1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="1.905" x2="0.889" y2="1.905" width="0.127" layer="51"/>
<wire x1="0.889" y1="1.905" x2="0.381" y2="1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="1.905" x2="-0.381" y2="1.905" width="0.127" layer="51"/>
<wire x1="-0.381" y1="1.905" x2="-0.889" y2="1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="1.905" x2="-1.651" y2="1.905" width="0.127" layer="51"/>
<wire x1="-1.651" y1="1.905" x2="-2.159" y2="1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="1.905" x2="-2.413" y2="1.905" width="0.127" layer="51"/>
<wire x1="-2.413" y1="1.905" x2="-2.413" y2="-1.397" width="0.127" layer="51"/>
<wire x1="-2.413" y1="-1.397" x2="-2.413" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-3.048" x2="-1.651" y2="-3.048" width="0.127" layer="51"/>
<wire x1="-1.651" y1="-3.048" x2="-1.651" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-1.651" y1="-2.667" x2="-1.651" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-3.048" x2="-2.159" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-2.667" x2="-2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-1.905" x2="-0.889" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-2.667" x2="-0.889" y2="-3.048" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-3.048" x2="-0.381" y2="-3.048" width="0.127" layer="51"/>
<wire x1="-0.381" y1="-3.048" x2="-0.381" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-0.381" y1="-2.667" x2="-0.381" y2="-1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="-1.905" x2="0.381" y2="-2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="-2.667" x2="0.381" y2="-3.048" width="0.127" layer="51"/>
<wire x1="0.381" y1="-3.048" x2="0.889" y2="-3.048" width="0.127" layer="51"/>
<wire x1="0.889" y1="-3.048" x2="0.889" y2="-2.667" width="0.127" layer="51"/>
<wire x1="0.889" y1="-2.667" x2="0.889" y2="-1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="-1.905" x2="1.651" y2="-2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="-2.667" x2="1.651" y2="-3.048" width="0.127" layer="51"/>
<wire x1="1.651" y1="-3.048" x2="2.159" y2="-3.048" width="0.127" layer="51"/>
<wire x1="2.159" y1="-3.048" x2="2.159" y2="-2.667" width="0.127" layer="51"/>
<wire x1="2.159" y1="-2.667" x2="2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="1.905" x2="-2.159" y2="2.667" width="0.127" layer="51"/>
<wire x1="-2.159" y1="2.667" x2="-2.159" y2="3.048" width="0.127" layer="51"/>
<wire x1="-2.159" y1="3.048" x2="-1.651" y2="3.048" width="0.127" layer="51"/>
<wire x1="-1.651" y1="3.048" x2="-1.651" y2="2.667" width="0.127" layer="51"/>
<wire x1="-1.651" y1="2.667" x2="-1.651" y2="1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="1.905" x2="-0.889" y2="2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="2.667" x2="-0.889" y2="3.048" width="0.127" layer="51"/>
<wire x1="-0.889" y1="3.048" x2="-0.381" y2="3.048" width="0.127" layer="51"/>
<wire x1="-0.381" y1="3.048" x2="-0.381" y2="2.667" width="0.127" layer="51"/>
<wire x1="-0.381" y1="2.667" x2="-0.381" y2="1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="1.905" x2="0.381" y2="2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="2.667" x2="0.381" y2="3.048" width="0.127" layer="51"/>
<wire x1="0.381" y1="3.048" x2="0.889" y2="3.048" width="0.127" layer="51"/>
<wire x1="0.889" y1="3.048" x2="0.889" y2="2.667" width="0.127" layer="51"/>
<wire x1="0.889" y1="2.667" x2="0.889" y2="1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="1.905" x2="1.651" y2="2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="2.667" x2="1.651" y2="3.048" width="0.127" layer="51"/>
<wire x1="1.651" y1="3.048" x2="2.159" y2="3.048" width="0.127" layer="51"/>
<wire x1="2.159" y1="3.048" x2="2.159" y2="2.667" width="0.127" layer="51"/>
<wire x1="2.159" y1="2.667" x2="2.159" y2="1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="2.667" x2="-1.651" y2="2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="2.667" x2="-0.381" y2="2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="2.667" x2="0.889" y2="2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="2.667" x2="2.159" y2="2.667" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-2.667" x2="-1.651" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-2.667" x2="-0.381" y2="-2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="-2.667" x2="0.889" y2="-2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="-2.667" x2="2.159" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-2.413" y1="-1.397" x2="2.413" y2="-1.397" width="0.127" layer="51"/>
<smd name="1" x="-1.905" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="2" x="-0.635" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="3" x="0.635" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="4" x="1.905" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="5" x="1.905" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="6" x="0.635" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="7" x="-0.635" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="8" x="-1.905" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<circle x="-1.778" y="-0.762" radius="0.254" width="0.127" layer="51"/>
<text x="-2.159" y="-0.127" size="0.6096" layer="25">&gt;NAME</text>
<text x="-2.159" y="0.889" size="0.6096" layer="27">&gt;VALUE</text>
</package>
<package name="SOT23">
<wire x1="1.143" y1="-0.635" x2="1.016" y2="-0.635" width="0.127" layer="51"/>
<wire x1="1.016" y1="-0.635" x2="0.508" y2="-0.635" width="0.127" layer="51"/>
<wire x1="0.508" y1="-0.635" x2="-0.508" y2="-0.635" width="0.127" layer="51"/>
<wire x1="-0.508" y1="-0.635" x2="-1.016" y2="-0.635" width="0.127" layer="51"/>
<wire x1="-1.016" y1="-0.635" x2="-1.143" y2="-0.635" width="0.127" layer="51"/>
<wire x1="-1.143" y1="-0.635" x2="-1.143" y2="0.635" width="0.127" layer="51"/>
<wire x1="-1.143" y1="0.635" x2="-0.254" y2="0.635" width="0.127" layer="51"/>
<wire x1="-0.254" y1="0.635" x2="0.254" y2="0.635" width="0.127" layer="51"/>
<wire x1="0.254" y1="0.635" x2="1.143" y2="0.635" width="0.127" layer="51"/>
<wire x1="1.143" y1="0.635" x2="1.143" y2="-0.635" width="0.127" layer="51"/>
<wire x1="1.016" y1="-0.635" x2="1.016" y2="-1.27" width="0.127" layer="51"/>
<wire x1="1.016" y1="-1.27" x2="0.508" y2="-1.27" width="0.127" layer="51"/>
<wire x1="0.508" y1="-1.27" x2="0.508" y2="-0.635" width="0.127" layer="51"/>
<wire x1="-0.508" y1="-0.635" x2="-0.508" y2="-1.27" width="0.127" layer="51"/>
<wire x1="-0.508" y1="-1.27" x2="-1.016" y2="-1.27" width="0.127" layer="51"/>
<wire x1="-1.016" y1="-1.27" x2="-1.016" y2="-0.635" width="0.127" layer="51"/>
<wire x1="-0.254" y1="0.635" x2="-0.254" y2="1.27" width="0.127" layer="51"/>
<wire x1="-0.254" y1="1.27" x2="0.254" y2="1.27" width="0.127" layer="51"/>
<wire x1="0.254" y1="1.27" x2="0.254" y2="0.635" width="0.127" layer="51"/>
<smd name="1" x="-0.762" y="-0.889" dx="1.016" dy="0.762" layer="1" rot="R90"/>
<smd name="2" x="0.762" y="-0.889" dx="1.016" dy="0.762" layer="1" rot="R90"/>
<smd name="3" x="0" y="0.889" dx="1.016" dy="0.762" layer="1" rot="R90"/>
<text x="1.524" y="-0.762" size="0.6096" layer="25">&gt;NAME</text>
<text x="1.524" y="0.254" size="0.6096" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MOSFET-P">
<pin name="G" x="-5.08" y="-2.54" visible="off" length="short"/>
<pin name="S" x="0" y="-5.08" visible="off" length="short" rot="R90"/>
<pin name="D" x="0" y="5.08" visible="off" length="short" rot="R270"/>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.905" y1="2.54" x2="-1.905" y2="1.905" width="0.254" layer="94"/>
<wire x1="-1.905" y1="1.905" x2="-1.905" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.905" y1="0.635" x2="-1.905" y2="0" width="0.254" layer="94"/>
<wire x1="-1.905" y1="0" x2="-1.905" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.27" x2="-1.905" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="-1.905" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="0" y1="-1.905" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-1.905" y1="1.905" x2="0" y2="1.905" width="0.254" layer="94"/>
<wire x1="0" y1="1.905" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0.635" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-0.635" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="0.635" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="-1.905" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="0.635" x2="2.54" y2="0.635" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.635" x2="1.905" y2="-0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="-0.635" x2="1.27" y2="0.635" width="0.254" layer="94"/>
<wire x1="1.27" y1="-0.635" x2="1.905" y2="-0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="-0.635" x2="2.54" y2="-0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="-0.635" x2="1.905" y2="-1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="-1.905" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="0.635" x2="1.905" y2="1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.905" x2="0" y2="1.905" width="0.254" layer="94"/>
<text x="3.175" y="-2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="3.175" y="0" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="MOSFET-N">
<pin name="G" x="-5.08" y="-2.54" visible="off" length="short"/>
<pin name="S" x="0" y="-5.08" visible="off" length="short" rot="R90"/>
<pin name="D" x="0" y="5.08" visible="off" length="short" rot="R270"/>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.905" y1="2.54" x2="-1.905" y2="1.905" width="0.254" layer="94"/>
<wire x1="-1.905" y1="1.905" x2="-1.905" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.905" y1="0.635" x2="-1.905" y2="0" width="0.254" layer="94"/>
<wire x1="-1.905" y1="0" x2="-1.905" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.27" x2="-1.905" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="-1.905" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="0" y1="-1.905" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-1.905" y1="1.905" x2="0" y2="1.905" width="0.254" layer="94"/>
<wire x1="0" y1="1.905" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.254" layer="94"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-0.635" y1="-0.635" x2="-1.905" y2="0" width="0.254" layer="94"/>
<wire x1="-1.905" y1="0" x2="-0.635" y2="0.635" width="0.254" layer="94"/>
<wire x1="1.27" y1="-0.635" x2="1.905" y2="0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="0.635" x2="2.54" y2="-0.635" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="-0.635" x2="1.27" y2="-0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="-0.635" x2="1.905" y2="-1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="-1.905" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="0.635" x2="1.905" y2="1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.905" x2="0" y2="1.905" width="0.254" layer="94"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="0.635" width="0.254" layer="94"/>
<wire x1="1.905" y1="0.635" x2="2.54" y2="0.635" width="0.254" layer="94"/>
<text x="3.175" y="0" size="1.778" layer="95">&gt;NAME</text>
<text x="3.175" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="TPC8120" prefix="T">
<gates>
<gate name="T1" symbol="MOSFET-P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOIC8">
<connects>
<connect gate="T1" pin="D" pad="5 6 7 8"/>
<connect gate="T1" pin="G" pad="4"/>
<connect gate="T1" pin="S" pad="1 2 3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="IRLML2502" prefix="T">
<gates>
<gate name="T1" symbol="MOSFET-N" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT23">
<connects>
<connect gate="T1" pin="D" pad="3"/>
<connect gate="T1" pin="G" pad="1"/>
<connect gate="T1" pin="S" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="allegro">
<packages>
<package name="SOIC8">
<wire x1="-2.413" y1="-1.905" x2="-2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-1.905" x2="-1.651" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-1.651" y1="-1.905" x2="-0.889" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-1.905" x2="-0.381" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-0.381" y1="-1.905" x2="0.381" y2="-1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="-1.905" x2="0.889" y2="-1.905" width="0.127" layer="51"/>
<wire x1="0.889" y1="-1.905" x2="1.651" y2="-1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="-1.905" x2="2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="2.159" y1="-1.905" x2="2.413" y2="-1.905" width="0.127" layer="51"/>
<wire x1="2.413" y1="-1.905" x2="2.413" y2="-1.397" width="0.127" layer="51"/>
<wire x1="2.413" y1="-1.397" x2="2.413" y2="1.905" width="0.127" layer="51"/>
<wire x1="2.413" y1="1.905" x2="2.159" y2="1.905" width="0.127" layer="51"/>
<wire x1="2.159" y1="1.905" x2="1.651" y2="1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="1.905" x2="0.889" y2="1.905" width="0.127" layer="51"/>
<wire x1="0.889" y1="1.905" x2="0.381" y2="1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="1.905" x2="-0.381" y2="1.905" width="0.127" layer="51"/>
<wire x1="-0.381" y1="1.905" x2="-0.889" y2="1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="1.905" x2="-1.651" y2="1.905" width="0.127" layer="51"/>
<wire x1="-1.651" y1="1.905" x2="-2.159" y2="1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="1.905" x2="-2.413" y2="1.905" width="0.127" layer="51"/>
<wire x1="-2.413" y1="1.905" x2="-2.413" y2="-1.397" width="0.127" layer="51"/>
<wire x1="-2.413" y1="-1.397" x2="-2.413" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-3.048" x2="-1.651" y2="-3.048" width="0.127" layer="51"/>
<wire x1="-1.651" y1="-3.048" x2="-1.651" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-1.651" y1="-2.667" x2="-1.651" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-3.048" x2="-2.159" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-2.667" x2="-2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-1.905" x2="-0.889" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-2.667" x2="-0.889" y2="-3.048" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-3.048" x2="-0.381" y2="-3.048" width="0.127" layer="51"/>
<wire x1="-0.381" y1="-3.048" x2="-0.381" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-0.381" y1="-2.667" x2="-0.381" y2="-1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="-1.905" x2="0.381" y2="-2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="-2.667" x2="0.381" y2="-3.048" width="0.127" layer="51"/>
<wire x1="0.381" y1="-3.048" x2="0.889" y2="-3.048" width="0.127" layer="51"/>
<wire x1="0.889" y1="-3.048" x2="0.889" y2="-2.667" width="0.127" layer="51"/>
<wire x1="0.889" y1="-2.667" x2="0.889" y2="-1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="-1.905" x2="1.651" y2="-2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="-2.667" x2="1.651" y2="-3.048" width="0.127" layer="51"/>
<wire x1="1.651" y1="-3.048" x2="2.159" y2="-3.048" width="0.127" layer="51"/>
<wire x1="2.159" y1="-3.048" x2="2.159" y2="-2.667" width="0.127" layer="51"/>
<wire x1="2.159" y1="-2.667" x2="2.159" y2="-1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="1.905" x2="-2.159" y2="2.667" width="0.127" layer="51"/>
<wire x1="-2.159" y1="2.667" x2="-2.159" y2="3.048" width="0.127" layer="51"/>
<wire x1="-2.159" y1="3.048" x2="-1.651" y2="3.048" width="0.127" layer="51"/>
<wire x1="-1.651" y1="3.048" x2="-1.651" y2="2.667" width="0.127" layer="51"/>
<wire x1="-1.651" y1="2.667" x2="-1.651" y2="1.905" width="0.127" layer="51"/>
<wire x1="-0.889" y1="1.905" x2="-0.889" y2="2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="2.667" x2="-0.889" y2="3.048" width="0.127" layer="51"/>
<wire x1="-0.889" y1="3.048" x2="-0.381" y2="3.048" width="0.127" layer="51"/>
<wire x1="-0.381" y1="3.048" x2="-0.381" y2="2.667" width="0.127" layer="51"/>
<wire x1="-0.381" y1="2.667" x2="-0.381" y2="1.905" width="0.127" layer="51"/>
<wire x1="0.381" y1="1.905" x2="0.381" y2="2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="2.667" x2="0.381" y2="3.048" width="0.127" layer="51"/>
<wire x1="0.381" y1="3.048" x2="0.889" y2="3.048" width="0.127" layer="51"/>
<wire x1="0.889" y1="3.048" x2="0.889" y2="2.667" width="0.127" layer="51"/>
<wire x1="0.889" y1="2.667" x2="0.889" y2="1.905" width="0.127" layer="51"/>
<wire x1="1.651" y1="1.905" x2="1.651" y2="2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="2.667" x2="1.651" y2="3.048" width="0.127" layer="51"/>
<wire x1="1.651" y1="3.048" x2="2.159" y2="3.048" width="0.127" layer="51"/>
<wire x1="2.159" y1="3.048" x2="2.159" y2="2.667" width="0.127" layer="51"/>
<wire x1="2.159" y1="2.667" x2="2.159" y2="1.905" width="0.127" layer="51"/>
<wire x1="-2.159" y1="2.667" x2="-1.651" y2="2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="2.667" x2="-0.381" y2="2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="2.667" x2="0.889" y2="2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="2.667" x2="2.159" y2="2.667" width="0.127" layer="51"/>
<wire x1="-2.159" y1="-2.667" x2="-1.651" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-2.667" x2="-0.381" y2="-2.667" width="0.127" layer="51"/>
<wire x1="0.381" y1="-2.667" x2="0.889" y2="-2.667" width="0.127" layer="51"/>
<wire x1="1.651" y1="-2.667" x2="2.159" y2="-2.667" width="0.127" layer="51"/>
<wire x1="-2.413" y1="-1.397" x2="2.413" y2="-1.397" width="0.127" layer="51"/>
<smd name="1" x="-1.905" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="2" x="-0.635" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="3" x="0.635" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="4" x="1.905" y="-2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="5" x="1.905" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="6" x="0.635" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="7" x="-0.635" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<smd name="8" x="-1.905" y="2.667" dx="1.27" dy="0.762" layer="1" rot="R90"/>
<circle x="-1.778" y="-0.762" radius="0.254" width="0.127" layer="51"/>
<text x="-2.159" y="-0.127" size="0.6096" layer="25">&gt;NAME</text>
<text x="-2.159" y="0.889" size="0.6096" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="ACS711">
<pin name="IP+" x="-15.24" y="5.08" length="middle"/>
<pin name="IP-" x="-15.24" y="-5.08" length="middle"/>
<pin name="GND" x="15.24" y="-5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="VCC" x="15.24" y="-2.54" length="middle" direction="pwr" rot="R180"/>
<pin name="NFAULT" x="15.24" y="2.54" length="middle" direction="oc" rot="R180"/>
<pin name="VIOUT" x="15.24" y="5.08" length="middle" rot="R180"/>
<wire x1="-10.16" y1="-7.62" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="7.62" x2="-10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="7.62" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<text x="-10.16" y="-10.16" size="2.032" layer="95">&gt;NAME</text>
<text x="10.16" y="-10.16" size="2.032" layer="96" align="bottom-right">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ACS711" prefix="U">
<gates>
<gate name="U1" symbol="ACS711" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOIC8">
<connects>
<connect gate="U1" pin="GND" pad="5"/>
<connect gate="U1" pin="IP+" pad="1 2"/>
<connect gate="U1" pin="IP-" pad="3 4"/>
<connect gate="U1" pin="NFAULT" pad="6"/>
<connect gate="U1" pin="VCC" pad="8"/>
<connect gate="U1" pin="VIOUT" pad="7"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ti">
<packages>
<package name="SOT23-6">
<text x="1.65" y="-0.85" size="0.6096" layer="25">&gt;NAME</text>
<text x="1.65" y="0.3" size="0.6096" layer="27">&gt;VALUE</text>
<smd name="1" x="-0.95" y="-1.35" dx="1.1" dy="0.6" layer="1" rot="R90"/>
<smd name="2" x="0" y="-1.35" dx="1.1" dy="0.6" layer="1" rot="R90"/>
<smd name="3" x="0.95" y="-1.35" dx="1.1" dy="0.6" layer="1" rot="R90"/>
<smd name="6" x="-0.95" y="1.35" dx="1.1" dy="0.6" layer="1" rot="R90"/>
<smd name="5" x="0" y="1.35" dx="1.1" dy="0.6" layer="1" rot="R90"/>
<smd name="4" x="0.95" y="1.35" dx="1.1" dy="0.6" layer="1" rot="R90"/>
<wire x1="-1.5" y1="0.85" x2="-1.2" y2="0.85" width="0.127" layer="51"/>
<wire x1="-1.2" y1="0.85" x2="-0.7" y2="0.85" width="0.127" layer="51"/>
<wire x1="-0.7" y1="0.85" x2="-0.25" y2="0.85" width="0.127" layer="51"/>
<wire x1="-0.25" y1="0.85" x2="0.25" y2="0.85" width="0.127" layer="51"/>
<wire x1="0.25" y1="0.85" x2="0.7" y2="0.85" width="0.127" layer="51"/>
<wire x1="0.7" y1="0.85" x2="1.2" y2="0.85" width="0.127" layer="51"/>
<wire x1="1.2" y1="0.85" x2="1.5" y2="0.85" width="0.127" layer="51"/>
<wire x1="1.5" y1="0.85" x2="1.5" y2="-0.85" width="0.127" layer="51"/>
<wire x1="1.5" y1="-0.85" x2="1.2" y2="-0.85" width="0.127" layer="51"/>
<wire x1="1.2" y1="-0.85" x2="0.7" y2="-0.85" width="0.127" layer="51"/>
<wire x1="0.7" y1="-0.85" x2="0.25" y2="-0.85" width="0.127" layer="51"/>
<wire x1="0.25" y1="-0.85" x2="-0.25" y2="-0.85" width="0.127" layer="51"/>
<wire x1="-0.25" y1="-0.85" x2="-0.7" y2="-0.85" width="0.127" layer="51"/>
<wire x1="-0.7" y1="-0.85" x2="-1.2" y2="-0.85" width="0.127" layer="51"/>
<wire x1="-1.2" y1="-0.85" x2="-1.5" y2="-0.85" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-0.85" x2="-1.5" y2="0.85" width="0.127" layer="51"/>
<circle x="-0.95" y="-0.45" radius="0.15" width="0.127" layer="51"/>
<wire x1="-0.25" y1="0.85" x2="-0.25" y2="1.5" width="0.127" layer="51"/>
<wire x1="-0.25" y1="1.5" x2="0.25" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.25" y1="1.5" x2="0.25" y2="0.85" width="0.127" layer="51"/>
<wire x1="0.7" y1="0.85" x2="0.7" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.7" y1="1.5" x2="1.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="1.2" y1="1.5" x2="1.2" y2="0.85" width="0.127" layer="51"/>
<wire x1="-1.2" y1="0.85" x2="-1.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="-1.2" y1="1.5" x2="-0.7" y2="1.5" width="0.127" layer="51"/>
<wire x1="-0.7" y1="1.5" x2="-0.7" y2="0.85" width="0.127" layer="51"/>
<wire x1="-1.2" y1="-0.85" x2="-1.2" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-1.2" y1="-1.5" x2="-0.7" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-0.7" y1="-1.5" x2="-0.7" y2="-0.85" width="0.127" layer="51"/>
<wire x1="-0.25" y1="-0.85" x2="-0.25" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-0.25" y1="-1.5" x2="0.25" y2="-1.5" width="0.127" layer="51"/>
<wire x1="0.25" y1="-1.5" x2="0.25" y2="-0.85" width="0.127" layer="51"/>
<wire x1="0.7" y1="-0.85" x2="0.7" y2="-1.5" width="0.127" layer="51"/>
<wire x1="0.7" y1="-1.5" x2="1.2" y2="-1.5" width="0.127" layer="51"/>
<wire x1="1.2" y1="-1.5" x2="1.2" y2="-0.85" width="0.127" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="LMR14203">
<wire x1="-10.16" y1="5.08" x2="-10.16" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-5.08" x2="10.16" y2="-5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="5.08" x2="-10.16" y2="5.08" width="0.254" layer="94"/>
<pin name="VIN" x="-15.24" y="2.54" length="middle" direction="pwr"/>
<pin name="SHDN" x="-15.24" y="0" length="middle" direction="in"/>
<pin name="GND" x="-15.24" y="-2.54" length="middle" direction="pwr"/>
<pin name="CB" x="15.24" y="2.54" length="middle" direction="pas" rot="R180"/>
<pin name="SW" x="15.24" y="0" length="middle" direction="out" rot="R180"/>
<pin name="FB" x="15.24" y="-2.54" length="middle" direction="in" rot="R180"/>
<text x="-10.16" y="-7.62" size="1.27" layer="95">&gt;NAME</text>
<text x="10.16" y="-7.62" size="1.27" layer="96" align="bottom-right">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="LMR14203" prefix="U">
<gates>
<gate name="U1" symbol="LMR14203" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT23-6">
<connects>
<connect gate="U1" pin="CB" pad="1"/>
<connect gate="U1" pin="FB" pad="3"/>
<connect gate="U1" pin="GND" pad="2"/>
<connect gate="U1" pin="SHDN" pad="4"/>
<connect gate="U1" pin="SW" pad="6"/>
<connect gate="U1" pin="VIN" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="oled">
<packages>
<package name="OLED_I2C_091">
<smd name="8" x="0" y="0.31" dx="2" dy="0.32" layer="1"/>
<smd name="7" x="0" y="-0.31" dx="2" dy="0.32" layer="1"/>
<smd name="9" x="0" y="0.93" dx="2" dy="0.32" layer="1"/>
<smd name="6" x="0" y="-0.93" dx="2" dy="0.32" layer="1"/>
<smd name="10" x="0" y="1.55" dx="2" dy="0.32" layer="1"/>
<smd name="5" x="0" y="-1.55" dx="2" dy="0.32" layer="1"/>
<smd name="11" x="0" y="2.17" dx="2" dy="0.32" layer="1"/>
<smd name="12" x="0" y="2.79" dx="2" dy="0.32" layer="1"/>
<smd name="13" x="0" y="3.41" dx="2" dy="0.32" layer="1"/>
<smd name="14" x="0" y="4.03" dx="2" dy="0.32" layer="1"/>
<smd name="4" x="0" y="-2.17" dx="2" dy="0.32" layer="1"/>
<smd name="3" x="0" y="-2.79" dx="2" dy="0.32" layer="1"/>
<smd name="2" x="0" y="-3.41" dx="2" dy="0.32" layer="1"/>
<smd name="1" x="0" y="-4.03" dx="2" dy="0.32" layer="1"/>
<wire x1="-23.8" y1="6.9" x2="3.1" y2="6.9" width="0.127" layer="51"/>
<wire x1="3.1" y1="6.9" x2="6.2" y2="6.9" width="0.127" layer="51"/>
<wire x1="6.2" y1="-4.6" x2="3.1" y2="-4.6" width="0.127" layer="51"/>
<wire x1="3.1" y1="-4.6" x2="-23.8" y2="-4.6" width="0.127" layer="51"/>
<wire x1="-23.8" y1="-4.6" x2="-23.8" y2="6.9" width="0.127" layer="51"/>
<wire x1="6.2" y1="6.9" x2="6.2" y2="3.5" width="0.127" layer="51"/>
<wire x1="6.2" y1="3.5" x2="6.2" y2="-3.5" width="0.127" layer="51"/>
<wire x1="6.2" y1="-3.5" x2="6.2" y2="-4.6" width="0.127" layer="51"/>
<wire x1="6.2" y1="3.5" x2="7.8" y2="3.5" width="0.127" layer="51"/>
<wire x1="7.8" y1="3.5" x2="7.8" y2="-3.5" width="0.127" layer="51"/>
<wire x1="7.8" y1="-3.5" x2="6.2" y2="-3.5" width="0.127" layer="51"/>
<wire x1="3.1" y1="6.9" x2="3.1" y2="-4.6" width="0.127" layer="51"/>
<wire x1="-22.7" y1="5.8" x2="1.7" y2="5.8" width="0.127" layer="51"/>
<wire x1="1.7" y1="5.8" x2="1.7" y2="-1.8" width="0.127" layer="51"/>
<wire x1="1.7" y1="-1.8" x2="-22.7" y2="-1.8" width="0.127" layer="51"/>
<wire x1="-22.7" y1="-1.8" x2="-22.7" y2="5.8" width="0.127" layer="51"/>
<wire x1="-21.7" y1="4.8" x2="0.7" y2="4.8" width="0.127" layer="51"/>
<wire x1="0.7" y1="4.8" x2="0.7" y2="-0.8" width="0.127" layer="51"/>
<wire x1="0.7" y1="-0.8" x2="-21.7" y2="-0.8" width="0.127" layer="51"/>
<wire x1="-21.7" y1="-0.8" x2="-21.7" y2="4.8" width="0.127" layer="51"/>
</package>
<package name="OLED_I2C_084">
<smd name="8" x="0" y="0.31" dx="2" dy="0.32" layer="1"/>
<smd name="7" x="0" y="-0.31" dx="2" dy="0.32" layer="1"/>
<smd name="9" x="0" y="0.93" dx="2" dy="0.32" layer="1"/>
<smd name="6" x="0" y="-0.93" dx="2" dy="0.32" layer="1"/>
<smd name="10" x="0" y="1.55" dx="2" dy="0.32" layer="1"/>
<smd name="5" x="0" y="-1.55" dx="2" dy="0.32" layer="1"/>
<smd name="11" x="0" y="2.17" dx="2" dy="0.32" layer="1"/>
<smd name="12" x="0" y="2.79" dx="2" dy="0.32" layer="1"/>
<smd name="13" x="0" y="3.41" dx="2" dy="0.32" layer="1"/>
<smd name="14" x="0" y="4.03" dx="2" dy="0.32" layer="1"/>
<smd name="4" x="0" y="-2.17" dx="2" dy="0.32" layer="1"/>
<smd name="3" x="0" y="-2.79" dx="2" dy="0.32" layer="1"/>
<smd name="2" x="0" y="-3.41" dx="2" dy="0.32" layer="1"/>
<smd name="1" x="0" y="-4.03" dx="2" dy="0.32" layer="1"/>
<wire x1="-23" y1="4.6" x2="2.5" y2="4.6" width="0.127" layer="51"/>
<wire x1="2.5" y1="4.6" x2="6.1" y2="4.6" width="0.127" layer="51"/>
<wire x1="6.1" y1="-4.6" x2="2.5" y2="-4.6" width="0.127" layer="51"/>
<wire x1="2.5" y1="-4.6" x2="-23" y2="-4.6" width="0.127" layer="51"/>
<wire x1="-23" y1="-4.6" x2="-23" y2="4.6" width="0.127" layer="51"/>
<wire x1="6.1" y1="4.6" x2="6.1" y2="3.5" width="0.127" layer="51"/>
<wire x1="6.1" y1="3.5" x2="6.1" y2="-3.5" width="0.127" layer="51"/>
<wire x1="6.1" y1="-3.5" x2="6.1" y2="-4.6" width="0.127" layer="51"/>
<wire x1="6.1" y1="3.5" x2="7.7" y2="3.5" width="0.127" layer="51"/>
<wire x1="7.7" y1="3.5" x2="7.7" y2="-3.5" width="0.127" layer="51"/>
<wire x1="7.7" y1="-3.5" x2="6.1" y2="-3.5" width="0.127" layer="51"/>
<wire x1="2.5" y1="4.6" x2="2.5" y2="-4.6" width="0.127" layer="51"/>
<wire x1="-21.9" y1="3.5" x2="1.2" y2="3.5" width="0.127" layer="51"/>
<wire x1="1.2" y1="3.5" x2="1.2" y2="-2" width="0.127" layer="51"/>
<wire x1="1.2" y1="-2" x2="-21.9" y2="-2" width="0.127" layer="51"/>
<wire x1="-21.9" y1="-2" x2="-21.9" y2="3.5" width="0.127" layer="51"/>
<wire x1="-20.9" y1="2.5" x2="0.2" y2="2.5" width="0.127" layer="51"/>
<wire x1="0.2" y1="2.5" x2="0.2" y2="-1" width="0.127" layer="51"/>
<wire x1="0.2" y1="-1" x2="-20.9" y2="-1" width="0.127" layer="51"/>
<wire x1="-20.9" y1="-1" x2="-20.9" y2="2.5" width="0.127" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="OLED_SSD1306_I2C">
<pin name="C2P" x="-15.24" y="17.78" length="middle" direction="pas"/>
<pin name="C2N" x="-15.24" y="15.24" length="middle" direction="pas"/>
<pin name="C1P" x="-15.24" y="12.7" length="middle" direction="pas"/>
<pin name="C1N" x="-15.24" y="10.16" length="middle" direction="pas"/>
<pin name="VBAT" x="-15.24" y="7.62" length="middle" direction="pwr"/>
<pin name="VBREF" x="-15.24" y="5.08" length="middle" direction="pas"/>
<pin name="VSS" x="-15.24" y="2.54" length="middle" direction="pwr"/>
<pin name="VDD" x="-15.24" y="0" length="middle" direction="pwr"/>
<pin name="NRES" x="-15.24" y="-2.54" length="middle" direction="in"/>
<pin name="SCL" x="-15.24" y="-5.08" length="middle" direction="in"/>
<pin name="SDA" x="-15.24" y="-7.62" length="middle" direction="in"/>
<pin name="IREF" x="-15.24" y="-10.16" length="middle" direction="pas"/>
<pin name="VCOM" x="-15.24" y="-12.7" length="middle" direction="pas"/>
<pin name="VCC" x="-15.24" y="-15.24" length="middle" direction="pwr"/>
<wire x1="-10.16" y1="20.32" x2="12.7" y2="20.32" width="0.254" layer="94"/>
<wire x1="12.7" y1="20.32" x2="12.7" y2="-17.78" width="0.254" layer="94"/>
<wire x1="12.7" y1="-17.78" x2="-10.16" y2="-17.78" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-17.78" x2="-10.16" y2="20.32" width="0.254" layer="94"/>
<text x="10.16" y="12.7" size="1.27" layer="94" align="bottom-right">OLED 0.84"
SSD1306
96 x 16</text>
<text x="10.16" y="-12.7" size="1.27" layer="95" align="bottom-right">&gt;NAME</text>
<text x="10.16" y="-15.24" size="1.27" layer="96" align="bottom-right">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="OLED_I2C" prefix="OLED">
<gates>
<gate name="OLED1" symbol="OLED_SSD1306_I2C" x="0" y="0"/>
</gates>
<devices>
<device name="_084" package="OLED_I2C_084">
<connects>
<connect gate="OLED1" pin="C1N" pad="4"/>
<connect gate="OLED1" pin="C1P" pad="3"/>
<connect gate="OLED1" pin="C2N" pad="2"/>
<connect gate="OLED1" pin="C2P" pad="1"/>
<connect gate="OLED1" pin="IREF" pad="12"/>
<connect gate="OLED1" pin="NRES" pad="9"/>
<connect gate="OLED1" pin="SCL" pad="10"/>
<connect gate="OLED1" pin="SDA" pad="11"/>
<connect gate="OLED1" pin="VBAT" pad="5"/>
<connect gate="OLED1" pin="VBREF" pad="6"/>
<connect gate="OLED1" pin="VCC" pad="14"/>
<connect gate="OLED1" pin="VCOM" pad="13"/>
<connect gate="OLED1" pin="VDD" pad="8"/>
<connect gate="OLED1" pin="VSS" pad="7"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_091" package="OLED_I2C_091">
<connects>
<connect gate="OLED1" pin="C1N" pad="4"/>
<connect gate="OLED1" pin="C1P" pad="3"/>
<connect gate="OLED1" pin="C2N" pad="2"/>
<connect gate="OLED1" pin="C2P" pad="1"/>
<connect gate="OLED1" pin="IREF" pad="12"/>
<connect gate="OLED1" pin="NRES" pad="9"/>
<connect gate="OLED1" pin="SCL" pad="10"/>
<connect gate="OLED1" pin="SDA" pad="11"/>
<connect gate="OLED1" pin="VBAT" pad="5"/>
<connect gate="OLED1" pin="VBREF" pad="6"/>
<connect gate="OLED1" pin="VCC" pad="14"/>
<connect gate="OLED1" pin="VCOM" pad="13"/>
<connect gate="OLED1" pin="VDD" pad="8"/>
<connect gate="OLED1" pin="VSS" pad="7"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diode">
<packages>
<package name="SOD123F">
<smd name="C" x="-1.35" y="0" dx="1.2" dy="1.2" layer="1"/>
<smd name="A" x="1.35" y="0" dx="1.2" dy="1.2" layer="1"/>
<wire x1="1.35" y1="0.85" x2="-0.9" y2="0.85" width="0.127" layer="51"/>
<wire x1="-0.9" y1="0.85" x2="-1.35" y2="0.85" width="0.127" layer="51"/>
<wire x1="-1.35" y1="0.85" x2="-1.35" y2="0.35" width="0.127" layer="51"/>
<wire x1="-1.35" y1="0.35" x2="-1.35" y2="-0.35" width="0.127" layer="51"/>
<wire x1="-1.35" y1="-0.35" x2="-1.35" y2="-0.85" width="0.127" layer="51"/>
<wire x1="-1.35" y1="-0.85" x2="-0.9" y2="-0.85" width="0.127" layer="51"/>
<wire x1="-0.9" y1="-0.85" x2="1.35" y2="-0.85" width="0.127" layer="51"/>
<wire x1="1.35" y1="-0.85" x2="1.35" y2="-0.35" width="0.127" layer="51"/>
<wire x1="1.35" y1="-0.35" x2="1.35" y2="0.35" width="0.127" layer="51"/>
<wire x1="1.35" y1="0.35" x2="1.35" y2="0.85" width="0.127" layer="51"/>
<wire x1="-1.35" y1="0.35" x2="-1.8" y2="0.35" width="0.127" layer="51"/>
<wire x1="-1.8" y1="0.35" x2="-1.8" y2="-0.35" width="0.127" layer="51"/>
<wire x1="-1.8" y1="-0.35" x2="-1.35" y2="-0.35" width="0.127" layer="51"/>
<wire x1="1.35" y1="0.35" x2="1.8" y2="0.35" width="0.127" layer="51"/>
<wire x1="1.8" y1="0.35" x2="1.8" y2="-0.35" width="0.127" layer="51"/>
<wire x1="1.8" y1="-0.35" x2="1.35" y2="-0.35" width="0.127" layer="51"/>
<wire x1="-0.9" y1="0.85" x2="-0.9" y2="-0.85" width="0.127" layer="51"/>
<text x="-1.4" y="-2.3" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.4" y="1" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="DFN1006">
<smd name="C" x="-0.35" y="0" dx="0.4" dy="0.7" layer="1"/>
<smd name="A" x="0.35" y="0" dx="0.4" dy="0.7" layer="1"/>
<wire x1="0.5" y1="0.3" x2="-0.2" y2="0.3" width="0.127" layer="51"/>
<wire x1="-0.2" y1="0.3" x2="-0.5" y2="0.3" width="0.127" layer="51"/>
<wire x1="-0.5" y1="0.3" x2="-0.5" y2="-0.3" width="0.127" layer="51"/>
<wire x1="-0.5" y1="-0.3" x2="-0.2" y2="-0.3" width="0.127" layer="51"/>
<wire x1="-0.2" y1="-0.3" x2="0.5" y2="-0.3" width="0.127" layer="51"/>
<wire x1="0.5" y1="-0.3" x2="0.5" y2="0.3" width="0.127" layer="51"/>
<wire x1="-0.2" y1="0.3" x2="-0.2" y2="-0.3" width="0.127" layer="51"/>
<text x="-0.55" y="-1.8" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.55" y="0.5" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="SOD323F">
<smd name="C" x="-1.35" y="0" dx="0.6" dy="0.6" layer="1"/>
<smd name="A" x="1.35" y="0" dx="0.6" dy="0.6" layer="1"/>
<wire x1="0.9" y1="0.7" x2="-0.4" y2="0.7" width="0.127" layer="51"/>
<wire x1="-0.4" y1="0.7" x2="-0.9" y2="0.7" width="0.127" layer="51"/>
<wire x1="-0.9" y1="0.7" x2="-0.9" y2="0.35" width="0.127" layer="51"/>
<wire x1="-0.9" y1="0.35" x2="-0.9" y2="-0.35" width="0.127" layer="51"/>
<wire x1="-0.9" y1="-0.35" x2="-0.9" y2="-0.7" width="0.127" layer="51"/>
<wire x1="-0.9" y1="-0.7" x2="-0.4" y2="-0.7" width="0.127" layer="51"/>
<wire x1="-0.4" y1="-0.7" x2="0.9" y2="-0.7" width="0.127" layer="51"/>
<wire x1="0.9" y1="-0.7" x2="0.9" y2="-0.35" width="0.127" layer="51"/>
<wire x1="0.9" y1="-0.35" x2="0.9" y2="0.35" width="0.127" layer="51"/>
<wire x1="0.9" y1="0.35" x2="0.9" y2="0.7" width="0.127" layer="51"/>
<wire x1="-0.9" y1="0.35" x2="-1.35" y2="0.35" width="0.127" layer="51"/>
<wire x1="-1.35" y1="0.35" x2="-1.35" y2="-0.35" width="0.127" layer="51"/>
<wire x1="-1.35" y1="-0.35" x2="-0.9" y2="-0.35" width="0.127" layer="51"/>
<wire x1="0.9" y1="0.35" x2="1.35" y2="0.35" width="0.127" layer="51"/>
<wire x1="1.35" y1="0.35" x2="1.35" y2="-0.35" width="0.127" layer="51"/>
<wire x1="1.35" y1="-0.35" x2="0.9" y2="-0.35" width="0.127" layer="51"/>
<wire x1="-0.4" y1="0.7" x2="-0.4" y2="-0.7" width="0.127" layer="51"/>
<text x="-1.4" y="-2.3" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.4" y="1" size="1.27" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="SHOTKY">
<pin name="C" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<pin name="A" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-0.635" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="-1.905" y="1.905" size="1.27" layer="95">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="DIODE">
<pin name="C" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<pin name="A" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="-1.905" y="1.905" size="1.27" layer="95">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="PMEG6010" prefix="D">
<gates>
<gate name="SHOTKY" symbol="SHOTKY" x="0" y="0"/>
</gates>
<devices>
<device name="CEH" package="SOD123F">
<connects>
<connect gate="SHOTKY" pin="A" pad="A"/>
<connect gate="SHOTKY" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CEJ" package="SOD323F">
<connects>
<connect gate="SHOTKY" pin="A" pad="A"/>
<connect gate="SHOTKY" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SBR02U100LP">
<gates>
<gate name="D" symbol="DIODE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DFN1006">
<connects>
<connect gate="D" pin="A" pad="A"/>
<connect gate="D" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="buttons">
<packages>
<package name="TST2435">
<wire x1="-2.25" y1="-1.35" x2="2.25" y2="-1.35" width="0.1" layer="51"/>
<wire x1="2.25" y1="-1.35" x2="2.25" y2="0.95" width="0.1" layer="51"/>
<wire x1="2.25" y1="0.95" x2="1" y2="0.95" width="0.1" layer="51"/>
<wire x1="1" y1="0.95" x2="-1" y2="0.95" width="0.1" layer="51"/>
<wire x1="-1" y1="0.95" x2="-2.25" y2="0.95" width="0.1" layer="51"/>
<wire x1="-2.25" y1="0.95" x2="-2.25" y2="-1.35" width="0.1" layer="51"/>
<hole x="-0.85" y="0" drill="0.7"/>
<hole x="0.85" y="0" drill="0.7"/>
<smd name="EP2" x="2.2" y="0.3" dx="0.8" dy="1" layer="1"/>
<smd name="EP1" x="-2.2" y="0.3" dx="0.8" dy="1" layer="1"/>
<wire x1="-2.25" y1="-0.85" x2="-1.85" y2="-0.85" width="0.1" layer="51"/>
<wire x1="-1.85" y1="-0.85" x2="-1.85" y2="-1.35" width="0.1" layer="51"/>
<wire x1="2.25" y1="-0.85" x2="1.85" y2="-0.85" width="0.1" layer="51"/>
<wire x1="1.85" y1="-0.85" x2="1.85" y2="-1.35" width="0.1" layer="51"/>
<smd name="1" x="-2" y="-1.15" dx="0.8" dy="0.9" layer="1"/>
<smd name="2" x="2" y="-1.15" dx="0.8" dy="0.9" layer="1"/>
<wire x1="-1" y1="0.95" x2="-1" y2="2.15" width="0.1" layer="51"/>
<wire x1="-1" y1="2.15" x2="1" y2="2.15" width="0.1" layer="51"/>
<wire x1="1" y1="2.15" x2="1" y2="0.95" width="0.1" layer="51"/>
<text x="-2.3" y="-2.6" size="1" layer="25">&gt;NAME</text>
<text x="-2.3" y="-3.7" size="1" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="BUTTON_SHIELD">
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<wire x1="-2.54" y1="0" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="1.27" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="-3.81" size="1.27" layer="95" align="top-left">&gt;NAME</text>
<text x="-5.08" y="3.81" size="1.27" layer="96" rot="R180" align="top-right">&gt;VALUE</text>
<wire x1="-3.81" y1="3.81" x2="-3.81" y2="-1.27" width="0.254" layer="94" style="shortdash"/>
<wire x1="-3.81" y1="-1.27" x2="0" y2="-1.27" width="0.254" layer="94" style="shortdash"/>
<wire x1="0" y1="-1.27" x2="3.81" y2="-1.27" width="0.254" layer="94" style="shortdash"/>
<wire x1="3.81" y1="-1.27" x2="3.81" y2="3.81" width="0.254" layer="94" style="shortdash"/>
<wire x1="3.81" y1="3.81" x2="-3.81" y2="3.81" width="0.254" layer="94" style="shortdash"/>
<pin name="SHIELD" x="0" y="-2.54" visible="off" length="point" direction="pas"/>
<wire x1="0" y1="-1.27" x2="0" y2="-2.54" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TST2435" prefix="SW">
<gates>
<gate name="SW1" symbol="BUTTON_SHIELD" x="0" y="0" swaplevel="1"/>
</gates>
<devices>
<device name="" package="TST2435">
<connects>
<connect gate="SW1" pin="1" pad="1"/>
<connect gate="SW1" pin="2" pad="2"/>
<connect gate="SW1" pin="SHIELD" pad="EP1 EP2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="test_point">
<packages>
<package name="SMD_15_60">
<smd name="TP" x="0" y="0" dx="0.381" dy="1.524" layer="1" rot="R90"/>
<text x="-0.508" y="0.508" size="0.635" layer="25">&gt;NAME</text>
<wire x1="-0.889" y1="0.3048" x2="0.889" y2="0.3048" width="0.127" layer="51"/>
<wire x1="0.889" y1="0.3048" x2="0.889" y2="-0.3048" width="0.127" layer="51"/>
<wire x1="0.889" y1="-0.3048" x2="-0.889" y2="-0.3048" width="0.127" layer="51"/>
<wire x1="-0.889" y1="-0.3048" x2="-0.889" y2="0.3048" width="0.127" layer="51"/>
</package>
<package name="SMD_12_48">
<smd name="TP" x="0" y="0" dx="0.3048" dy="1.2192" layer="1" rot="R90"/>
<text x="-0.508" y="0.508" size="0.635" layer="25">&gt;NAME</text>
<wire x1="-0.762" y1="0.254" x2="0.762" y2="0.254" width="0.127" layer="51"/>
<wire x1="0.762" y1="0.254" x2="0.762" y2="-0.254" width="0.127" layer="51"/>
<wire x1="0.762" y1="-0.254" x2="-0.762" y2="-0.254" width="0.127" layer="51"/>
<wire x1="-0.762" y1="-0.254" x2="-0.762" y2="0.254" width="0.127" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="TEST_PAD">
<pin name="TP" x="-2.54" y="0" visible="off" length="short"/>
<rectangle x1="0" y1="-0.635" x2="2.54" y2="0.635" layer="94"/>
<text x="-1.27" y="1.27" size="1.27" layer="95">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="TEST_PAD" prefix="TP">
<gates>
<gate name="TP" symbol="TEST_PAD" x="0" y="0"/>
</gates>
<devices>
<device name="12X48" package="SMD_12_48">
<connects>
<connect gate="TP" pin="TP" pad="TP"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="15X60" package="SMD_15_60">
<connects>
<connect gate="TP" pin="TP" pad="TP"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pinhead">
<packages>
<package name="PINHEAD1X3">
<pad name="1" x="-2.54" y="0" drill="0.8" shape="square"/>
<wire x1="-1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.127" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.81" y2="0.635" width="0.127" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-0.635" x2="-3.175" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-1.905" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-1.27" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-1.27" y2="0.635" width="0.127" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.905" y2="1.27" width="0.127" layer="21"/>
<pad name="2" x="0" y="0" drill="0.8" shape="octagon"/>
<wire x1="-1.27" y1="0.635" x2="-0.635" y2="1.27" width="0.127" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.127" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.127" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.127" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.27" y2="-0.635" width="0.127" layer="21"/>
<pad name="3" x="2.54" y="0" drill="0.8" shape="octagon"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.127" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.127" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.127" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.127" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.127" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.127" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.127" layer="21"/>
</package>
<package name="PIN1X3">
<pad name="1" x="-2.54" y="0" drill="0.9" shape="square"/>
<pad name="2" x="0" y="0" drill="0.9" shape="octagon"/>
<pad name="3" x="2.54" y="0" drill="0.9" shape="octagon"/>
</package>
</packages>
<symbols>
<symbol name="PINHEAD1X3">
<pin name="1" x="-5.08" y="2.54" length="middle"/>
<pin name="2" x="-5.08" y="0" length="middle"/>
<pin name="3" x="-5.08" y="-2.54" length="middle"/>
<wire x1="0" y1="5.08" x2="0" y2="-5.08" width="0.254" layer="94"/>
<wire x1="0" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="0" y2="5.08" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHEAD1X3">
<gates>
<gate name="P" symbol="PINHEAD1X3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="PINHEAD1X3">
<connects>
<connect gate="P" pin="1" pad="1"/>
<connect gate="P" pin="2" pad="2"/>
<connect gate="P" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="X" package="PIN1X3">
<connects>
<connect gate="P" pin="1" pad="1"/>
<connect gate="P" pin="2" pad="2"/>
<connect gate="P" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply">
<packages>
</packages>
<symbols>
<symbol name="3V3">
<pin name="3V3" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
<wire x1="-1.27" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<text x="0" y="3.81" size="1.778" layer="96" align="center">&gt;VALUE</text>
</symbol>
<symbol name="VDDA">
<pin name="VDDA" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
<wire x1="-1.27" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<text x="0" y="3.81" size="1.778" layer="96" align="center">&gt;VALUE</text>
</symbol>
<symbol name="12V">
<pin name="12V" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
<wire x1="-1.27" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<text x="0" y="3.81" size="1.778" layer="96" align="center">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="3V3" prefix="3V3">
<gates>
<gate name="3V3" symbol="3V3" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VDDA" prefix="VDDA">
<gates>
<gate name="VDDA" symbol="VDDA" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="12V" prefix="12V">
<gates>
<gate name="12V" symbol="12V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="RT" library="weller_rt" deviceset="RT-1" device=""/>
<part name="FRAME1" library="frames" deviceset="A4L-LOC" device="" value="RT-SOLDER"/>
<part name="U2" library="stm32" deviceset="STM32F031GX" device=""/>
<part name="GND2" library="supply1" deviceset="GND" device=""/>
<part name="GND3" library="supply1" deviceset="GND" device=""/>
<part name="GND4" library="supply1" deviceset="GND" device=""/>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="GND6" library="supply1" deviceset="GND" device=""/>
<part name="U3" library="analog_devices" deviceset="AD8551" device="RM"/>
<part name="R6" library="rlc" deviceset="R" device="0402" value="5k6"/>
<part name="R7" library="rlc" deviceset="R" device="0402" value="100k(82k)"/>
<part name="R9" library="rlc" deviceset="R" device="0402" value="5k6"/>
<part name="R8" library="rlc" deviceset="R" device="0402" value="270R(220R)"/>
<part name="C13" library="rlc" deviceset="C" device="0402" value="1n"/>
<part name="C11" library="rlc" deviceset="C" device="0402" value="100n"/>
<part name="C14" library="rlc" deviceset="C" device="0402" value="1n"/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="JACK" library="jack" deviceset="SJ-3501-SMT" device=""/>
<part name="GND7" library="supply1" deviceset="GND" device=""/>
<part name="C10" library="rlc" deviceset="C" device="0402" value="10n"/>
<part name="GND8" library="supply1" deviceset="GND" device=""/>
<part name="C7" library="rlc" deviceset="C" device="0402" value="100n"/>
<part name="GND9" library="supply1" deviceset="GND" device=""/>
<part name="C9" library="rlc" deviceset="C" device="0402" value="100n"/>
<part name="GND10" library="supply1" deviceset="GND" device=""/>
<part name="T1" library="mosfet" deviceset="TPC8120" device=""/>
<part name="R12" library="rlc" deviceset="R" device="0402" value="4k7"/>
<part name="T2" library="mosfet" deviceset="IRLML2502" device="" value="BSS816-SOT323"/>
<part name="GND11" library="supply1" deviceset="GND" device=""/>
<part name="GND12" library="supply1" deviceset="GND" device=""/>
<part name="U4" library="allegro" deviceset="ACS711" device=""/>
<part name="L2" library="rlc" deviceset="L" device="0805" value="2.2uH"/>
<part name="U1" library="ti" deviceset="LMR14203" device=""/>
<part name="L1" library="rlc" deviceset="L" device="1717" value="68uH"/>
<part name="C5" library="rlc" deviceset="C" device="0402" value="150n (220n)"/>
<part name="C3" library="rlc" deviceset="C" device="0805" value="2.2uF/25V"/>
<part name="C6" library="rlc" deviceset="C" device="0805" value="22uF"/>
<part name="GND13" library="supply1" deviceset="GND" device=""/>
<part name="GND14" library="supply1" deviceset="GND" device=""/>
<part name="GND15" library="supply1" deviceset="GND" device=""/>
<part name="GND16" library="supply1" deviceset="GND" device=""/>
<part name="GND17" library="supply1" deviceset="GND" device=""/>
<part name="R2" library="rlc" deviceset="R" device="0402" value="1k (820R)"/>
<part name="R1" library="rlc" deviceset="R" device="0402" value="3k3 (2k7)"/>
<part name="C19" library="rlc" deviceset="C" device="0603" value="2.2uF/16V"/>
<part name="C20" library="rlc" deviceset="C" device="0603" value="2.2uF/16V"/>
<part name="C18" library="rlc" deviceset="C" device="0603" value="1uF"/>
<part name="C17" library="rlc" deviceset="C" device="0603" value="1uF"/>
<part name="GND20" library="supply1" deviceset="GND" device=""/>
<part name="R15" library="rlc" deviceset="R" device="0402" value="390k"/>
<part name="C15" library="rlc" deviceset="C" device="0603" value="1uF"/>
<part name="C16" library="rlc" deviceset="C" device="0603" value="1uF"/>
<part name="D2" library="diode" deviceset="PMEG6010" device="CEH"/>
<part name="GND18" library="supply1" deviceset="GND" device=""/>
<part name="OLED1" library="oled" deviceset="OLED_I2C" device="_091"/>
<part name="C8" library="rlc" deviceset="C" device="0603" value="1uF"/>
<part name="GND19" library="supply1" deviceset="GND" device=""/>
<part name="GND21" library="supply1" deviceset="GND" device=""/>
<part name="R13" library="rlc" deviceset="R" device="0402" value="10k"/>
<part name="R14" library="rlc" deviceset="R" device="0402" value="10k"/>
<part name="R10" library="rlc" deviceset="R" device="0402" value="10k"/>
<part name="TP1" library="test_point" deviceset="TEST_PAD" device="15X60"/>
<part name="D1" library="diode" deviceset="PMEG6010" device="CEH" value="PMEG6010CEH"/>
<part name="C4" library="rlc" deviceset="C" device="0402" value="100n"/>
<part name="GND22" library="supply1" deviceset="GND" device=""/>
<part name="R3" library="rlc" deviceset="R" device="0402" value="68k*"/>
<part name="R4" library="rlc" deviceset="R" device="0402" value="10k*"/>
<part name="GND23" library="supply1" deviceset="GND" device=""/>
<part name="D4" library="diode" deviceset="SBR02U100LP" device=""/>
<part name="D3" library="diode" deviceset="SBR02U100LP" device=""/>
<part name="GND24" library="supply1" deviceset="GND" device=""/>
<part name="GND25" library="supply1" deviceset="GND" device=""/>
<part name="C12" library="rlc" deviceset="C" device="0603" value="2.2n"/>
<part name="GND26" library="supply1" deviceset="GND" device=""/>
<part name="R5" library="rlc" deviceset="R" device="0402" value="1M"/>
<part name="C1" library="rlc" deviceset="C" device="1206" value="22uF"/>
<part name="C2" library="rlc" deviceset="C" device="0402" value="100n"/>
<part name="GND27" library="supply1" deviceset="GND" device=""/>
<part name="GND28" library="supply1" deviceset="GND" device=""/>
<part name="SWD" library="pinhead" deviceset="PINHEAD1X3" device="X"/>
<part name="SW1" library="buttons" deviceset="TST2435" device=""/>
<part name="SW2" library="buttons" deviceset="TST2435" device=""/>
<part name="R11" library="rlc" deviceset="R" device="0402" value="4k7"/>
<part name="3V2" library="supply" deviceset="3V3" device=""/>
<part name="VDDA1" library="supply" deviceset="VDDA" device=""/>
<part name="VDDA2" library="supply" deviceset="VDDA" device=""/>
<part name="VDDA3" library="supply" deviceset="VDDA" device=""/>
<part name="VDDA4" library="supply" deviceset="VDDA" device=""/>
<part name="3V3" library="supply" deviceset="3V3" device=""/>
<part name="12V1" library="supply" deviceset="12V" device=""/>
<part name="12V3" library="supply" deviceset="12V" device=""/>
<part name="12V4" library="supply" deviceset="12V" device=""/>
<part name="VDDA5" library="supply" deviceset="VDDA" device=""/>
<part name="3V1" library="supply" deviceset="3V3" device=""/>
<part name="3V4" library="supply" deviceset="3V3" device=""/>
<part name="3V5" library="supply" deviceset="3V3" device=""/>
<part name="12V2" library="supply" deviceset="12V" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="88.9" y="142.24" size="1.778" layer="97">K-type sensor:
500°C = 8.08mV = 3.000V</text>
<text x="248.92" y="119.38" size="1.778" layer="95" rot="R90" align="bottom-center">SWD</text>
<wire x1="5.08" y1="5.08" x2="139.7" y2="5.08" width="0.1524" layer="97"/>
<wire x1="139.7" y1="5.08" x2="139.7" y2="43.18" width="0.1524" layer="97"/>
<wire x1="139.7" y1="43.18" x2="5.08" y2="43.18" width="0.1524" layer="97"/>
<wire x1="5.08" y1="43.18" x2="5.08" y2="5.08" width="0.1524" layer="97"/>
<text x="15.24" y="40.64" size="1.778" layer="97">Power supply</text>
<wire x1="5.08" y1="45.72" x2="139.7" y2="45.72" width="0.1524" layer="97"/>
<wire x1="139.7" y1="45.72" x2="139.7" y2="93.98" width="0.1524" layer="97"/>
<wire x1="139.7" y1="93.98" x2="5.08" y2="93.98" width="0.1524" layer="97"/>
<wire x1="5.08" y1="93.98" x2="5.08" y2="45.72" width="0.1524" layer="97"/>
<text x="7.62" y="91.44" size="1.778" layer="97">Heater power switch and current sensor</text>
<wire x1="5.08" y1="96.52" x2="139.7" y2="96.52" width="0.1524" layer="97"/>
<wire x1="5.08" y1="96.52" x2="5.08" y2="149.86" width="0.1524" layer="97"/>
<wire x1="5.08" y1="149.86" x2="139.7" y2="149.86" width="0.1524" layer="97"/>
<wire x1="139.7" y1="149.86" x2="139.7" y2="96.52" width="0.1524" layer="97"/>
<text x="7.62" y="147.32" size="1.778" layer="97">Temperature sensor amplifier</text>
<wire x1="5.08" y1="152.4" x2="139.7" y2="152.4" width="0.1524" layer="97"/>
<wire x1="139.7" y1="152.4" x2="139.7" y2="172.72" width="0.1524" layer="97"/>
<wire x1="139.7" y1="172.72" x2="5.08" y2="172.72" width="0.1524" layer="97"/>
<wire x1="5.08" y1="172.72" x2="5.08" y2="152.4" width="0.1524" layer="97"/>
<text x="7.62" y="170.18" size="1.778" layer="97">Connector for RT soldering pen</text>
<wire x1="142.24" y1="106.68" x2="254" y2="106.68" width="0.1524" layer="97"/>
<wire x1="254" y1="106.68" x2="254" y2="172.72" width="0.1524" layer="97"/>
<wire x1="254" y1="172.72" x2="142.24" y2="172.72" width="0.1524" layer="97"/>
<wire x1="142.24" y1="172.72" x2="142.24" y2="106.68" width="0.1524" layer="97"/>
<text x="144.78" y="170.18" size="1.778" layer="97">Microcontroller</text>
<wire x1="254" y1="25.4" x2="175.26" y2="25.4" width="0.1524" layer="97"/>
<wire x1="175.26" y1="25.4" x2="175.26" y2="78.74" width="0.1524" layer="97"/>
<wire x1="175.26" y1="78.74" x2="254" y2="78.74" width="0.1524" layer="97"/>
<wire x1="254" y1="78.74" x2="254" y2="25.4" width="0.1524" layer="97"/>
<text x="177.8" y="76.2" size="1.778" layer="97">DISPLAY</text>
<wire x1="172.72" y1="25.4" x2="142.24" y2="25.4" width="0.1524" layer="97"/>
<wire x1="142.24" y1="25.4" x2="142.24" y2="78.74" width="0.1524" layer="97"/>
<wire x1="142.24" y1="78.74" x2="172.72" y2="78.74" width="0.1524" layer="97"/>
<wire x1="172.72" y1="78.74" x2="172.72" y2="25.4" width="0.1524" layer="97"/>
<text x="144.78" y="73.66" size="1.778" layer="97">Supply voltage
measurement</text>
<wire x1="254" y1="81.28" x2="254" y2="104.14" width="0.1524" layer="97"/>
<wire x1="254" y1="104.14" x2="142.24" y2="104.14" width="0.1524" layer="97"/>
<wire x1="142.24" y1="104.14" x2="142.24" y2="81.28" width="0.1524" layer="97"/>
<wire x1="142.24" y1="81.28" x2="254" y2="81.28" width="0.1524" layer="97"/>
<text x="144.78" y="101.6" size="1.778" layer="97">Buttons</text>
</plain>
<instances>
<instance part="RT" gate="G$1" x="86.36" y="167.64"/>
<instance part="FRAME1" gate="G$1" x="0" y="0"/>
<instance part="U2" gate="U" x="198.12" y="142.24"/>
<instance part="GND2" gate="1" x="53.34" y="101.6"/>
<instance part="GND3" gate="1" x="60.96" y="101.6"/>
<instance part="GND4" gate="1" x="76.2" y="101.6"/>
<instance part="GND5" gate="1" x="114.3" y="101.6"/>
<instance part="GND6" gate="1" x="91.44" y="101.6"/>
<instance part="U3" gate="IC" x="76.2" y="121.92"/>
<instance part="R6" gate="R" x="30.48" y="124.46"/>
<instance part="R7" gate="R" x="68.58" y="132.08"/>
<instance part="R9" gate="R" x="106.68" y="121.92"/>
<instance part="R8" gate="R" x="60.96" y="111.76" rot="R90"/>
<instance part="C13" gate="C" x="53.34" y="111.76" rot="R90"/>
<instance part="C11" gate="C" x="91.44" y="111.76" rot="R90"/>
<instance part="C14" gate="C" x="114.3" y="111.76" rot="R90"/>
<instance part="GND1" gate="1" x="104.14" y="157.48"/>
<instance part="JACK" gate="CON" x="104.14" y="167.64" rot="R270"/>
<instance part="GND7" gate="1" x="170.18" y="111.76"/>
<instance part="C10" gate="C" x="162.56" y="119.38" rot="R90"/>
<instance part="GND8" gate="1" x="162.56" y="111.76"/>
<instance part="C7" gate="C" x="116.84" y="20.32" rot="R90"/>
<instance part="GND9" gate="1" x="116.84" y="10.16"/>
<instance part="C9" gate="C" x="154.94" y="119.38" rot="R90"/>
<instance part="GND10" gate="1" x="154.94" y="111.76"/>
<instance part="T1" gate="T1" x="71.12" y="78.74" smashed="yes" rot="MR90">
<attribute name="NAME" x="73.025" y="73.66" size="1.778" layer="95" rot="MR0"/>
<attribute name="VALUE" x="66.675" y="83.82" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R12" gate="R" x="58.42" y="76.2"/>
<instance part="T2" gate="T1" x="50.8" y="63.5"/>
<instance part="GND11" gate="1" x="50.8" y="50.8"/>
<instance part="GND12" gate="1" x="111.76" y="50.8"/>
<instance part="U4" gate="U1" x="93.98" y="73.66"/>
<instance part="L2" gate="L1" x="124.46" y="27.94"/>
<instance part="U1" gate="U1" x="66.04" y="30.48"/>
<instance part="L1" gate="L1" x="99.06" y="33.02"/>
<instance part="C5" gate="C" x="86.36" y="33.02"/>
<instance part="C3" gate="C" x="33.02" y="22.86" rot="R90"/>
<instance part="C6" gate="C" x="106.68" y="20.32" rot="R90"/>
<instance part="GND13" gate="1" x="106.68" y="10.16"/>
<instance part="GND14" gate="1" x="91.44" y="10.16"/>
<instance part="GND15" gate="1" x="83.82" y="10.16"/>
<instance part="GND16" gate="1" x="33.02" y="10.16"/>
<instance part="GND17" gate="1" x="48.26" y="10.16"/>
<instance part="R2" gate="R" x="83.82" y="20.32" rot="R90"/>
<instance part="R1" gate="R" x="99.06" y="27.94"/>
<instance part="C19" gate="C" x="215.9" y="35.56"/>
<instance part="C20" gate="C" x="205.74" y="38.1"/>
<instance part="C18" gate="C" x="215.9" y="68.58" rot="R180"/>
<instance part="C17" gate="C" x="215.9" y="63.5" rot="R180"/>
<instance part="GND20" gate="1" x="200.66" y="30.48"/>
<instance part="R15" gate="R" x="215.9" y="40.64"/>
<instance part="C15" gate="C" x="215.9" y="58.42" rot="R180"/>
<instance part="C16" gate="C" x="215.9" y="50.8" rot="R180"/>
<instance part="D2" gate="SHOTKY" x="91.44" y="20.32" rot="R270"/>
<instance part="GND18" gate="1" x="198.12" y="86.36"/>
<instance part="OLED1" gate="OLED1" x="238.76" y="50.8"/>
<instance part="C8" gate="C" x="132.08" y="20.32" rot="R90"/>
<instance part="GND19" gate="1" x="132.08" y="10.16"/>
<instance part="GND21" gate="1" x="226.06" y="111.76"/>
<instance part="R13" gate="R" x="193.04" y="58.42" rot="R90"/>
<instance part="R14" gate="R" x="198.12" y="63.5" rot="R90"/>
<instance part="R10" gate="R" x="43.18" y="55.88"/>
<instance part="TP1" gate="TP" x="248.92" y="157.48"/>
<instance part="D1" gate="SHOTKY" x="25.4" y="30.48" rot="R180"/>
<instance part="C4" gate="C" x="40.64" y="22.86" rot="R90"/>
<instance part="GND22" gate="1" x="40.64" y="10.16"/>
<instance part="R3" gate="R" x="147.32" y="55.88" rot="R90"/>
<instance part="R4" gate="R" x="147.32" y="40.64" rot="R90"/>
<instance part="GND23" gate="1" x="147.32" y="30.48"/>
<instance part="D4" gate="D" x="45.72" y="111.76" rot="R90"/>
<instance part="D3" gate="D" x="38.1" y="111.76" rot="R270"/>
<instance part="GND24" gate="1" x="45.72" y="101.6"/>
<instance part="GND25" gate="1" x="38.1" y="101.6"/>
<instance part="C12" gate="C" x="99.06" y="111.76" rot="R90"/>
<instance part="GND26" gate="1" x="99.06" y="101.6"/>
<instance part="R5" gate="R" x="22.86" y="132.08" rot="R90"/>
<instance part="C1" gate="C" x="10.16" y="22.86" rot="R90"/>
<instance part="C2" gate="C" x="17.78" y="22.86" rot="R90"/>
<instance part="GND27" gate="1" x="10.16" y="10.16"/>
<instance part="GND28" gate="1" x="17.78" y="10.16"/>
<instance part="SWD" gate="P" x="241.3" y="119.38" rot="MR180"/>
<instance part="SW1" gate="SW1" x="208.28" y="96.52" rot="MR0"/>
<instance part="SW2" gate="SW1" x="187.96" y="96.52" rot="MR0"/>
<instance part="R11" gate="R" x="58.42" y="71.12"/>
<instance part="3V2" gate="3V3" x="116.84" y="35.56"/>
<instance part="VDDA1" gate="VDDA" x="132.08" y="35.56"/>
<instance part="VDDA2" gate="VDDA" x="76.2" y="139.7"/>
<instance part="VDDA3" gate="VDDA" x="154.94" y="134.62"/>
<instance part="VDDA4" gate="VDDA" x="111.76" y="83.82"/>
<instance part="3V3" gate="3V3" x="147.32" y="134.62"/>
<instance part="12V1" gate="12V" x="10.16" y="35.56"/>
<instance part="12V3" gate="12V" x="147.32" y="63.5"/>
<instance part="12V4" gate="12V" x="50.8" y="83.82"/>
<instance part="VDDA5" gate="VDDA" x="22.86" y="139.7"/>
<instance part="3V1" gate="3V3" x="220.98" y="71.12"/>
<instance part="3V4" gate="3V3" x="193.04" y="71.12"/>
<instance part="3V5" gate="3V3" x="198.12" y="71.12"/>
<instance part="12V2" gate="12V" x="63.5" y="83.82"/>
</instances>
<busses>
</busses>
<nets>
<net name="SENSOR_IN" class="0">
<segment>
<wire x1="66.04" y1="124.46" x2="53.34" y2="124.46" width="0.1524" layer="91"/>
<wire x1="53.34" y1="124.46" x2="45.72" y2="124.46" width="0.1524" layer="91"/>
<wire x1="45.72" y1="124.46" x2="38.1" y2="124.46" width="0.1524" layer="91"/>
<wire x1="38.1" y1="124.46" x2="35.56" y2="124.46" width="0.1524" layer="91"/>
<wire x1="53.34" y1="114.3" x2="53.34" y2="124.46" width="0.1524" layer="91"/>
<junction x="53.34" y="124.46"/>
<pinref part="U3" gate="IC" pin="IN+"/>
<pinref part="R6" gate="R" pin="2"/>
<pinref part="C13" gate="C" pin="2"/>
<pinref part="D3" gate="D" pin="C"/>
<wire x1="38.1" y1="116.84" x2="38.1" y2="124.46" width="0.1524" layer="91"/>
<junction x="38.1" y="124.46"/>
<pinref part="D4" gate="D" pin="A"/>
<wire x1="45.72" y1="116.84" x2="45.72" y2="124.46" width="0.1524" layer="91"/>
<junction x="45.72" y="124.46"/>
</segment>
</net>
<net name="SENSOR_FEEDBACK" class="0">
<segment>
<wire x1="60.96" y1="116.84" x2="60.96" y2="119.38" width="0.1524" layer="91"/>
<wire x1="60.96" y1="119.38" x2="66.04" y2="119.38" width="0.1524" layer="91"/>
<wire x1="60.96" y1="119.38" x2="60.96" y2="132.08" width="0.1524" layer="91"/>
<wire x1="60.96" y1="132.08" x2="63.5" y2="132.08" width="0.1524" layer="91"/>
<junction x="60.96" y="119.38"/>
<pinref part="U3" gate="IC" pin="IN-"/>
<pinref part="R7" gate="R" pin="1"/>
<pinref part="R8" gate="R" pin="2"/>
</segment>
</net>
<net name="SENSOR_OUT" class="0">
<segment>
<wire x1="73.66" y1="132.08" x2="88.9" y2="132.08" width="0.1524" layer="91"/>
<wire x1="88.9" y1="132.08" x2="88.9" y2="121.92" width="0.1524" layer="91"/>
<wire x1="88.9" y1="121.92" x2="86.36" y2="121.92" width="0.1524" layer="91"/>
<wire x1="88.9" y1="121.92" x2="101.6" y2="121.92" width="0.1524" layer="91"/>
<junction x="88.9" y="121.92"/>
<pinref part="U3" gate="IC" pin="OUT"/>
<pinref part="R7" gate="R" pin="2"/>
<pinref part="R9" gate="R" pin="1"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="91.44" y1="109.22" x2="91.44" y2="104.14" width="0.1524" layer="91"/>
<pinref part="C11" gate="C" pin="1"/>
</segment>
<segment>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="76.2" y1="114.3" x2="76.2" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U3" gate="IC" pin="V-"/>
</segment>
<segment>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="114.3" y1="109.22" x2="114.3" y2="104.14" width="0.1524" layer="91"/>
<pinref part="C14" gate="C" pin="1"/>
</segment>
<segment>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="60.96" y1="106.68" x2="60.96" y2="104.14" width="0.1524" layer="91"/>
<pinref part="R8" gate="R" pin="1"/>
</segment>
<segment>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="53.34" y1="109.22" x2="53.34" y2="104.14" width="0.1524" layer="91"/>
<pinref part="C13" gate="C" pin="1"/>
</segment>
<segment>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="104.14" y1="162.56" x2="104.14" y2="160.02" width="0.1524" layer="91"/>
<pinref part="JACK" gate="CON" pin="1"/>
</segment>
<segment>
<pinref part="C10" gate="C" pin="1"/>
<pinref part="GND8" gate="1" pin="GND"/>
<wire x1="162.56" y1="116.84" x2="162.56" y2="114.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND7" gate="1" pin="GND"/>
<pinref part="U2" gate="U" pin="VSS"/>
<wire x1="170.18" y1="114.3" x2="170.18" y2="124.46" width="0.1524" layer="91"/>
<wire x1="170.18" y1="124.46" x2="172.72" y2="124.46" width="0.1524" layer="91"/>
<pinref part="U2" gate="U" pin="BOOT0"/>
<wire x1="170.18" y1="124.46" x2="170.18" y2="134.62" width="0.1524" layer="91"/>
<wire x1="170.18" y1="134.62" x2="172.72" y2="134.62" width="0.1524" layer="91"/>
<junction x="170.18" y="124.46"/>
</segment>
<segment>
<pinref part="C7" gate="C" pin="1"/>
<wire x1="116.84" y1="17.78" x2="116.84" y2="12.7" width="0.1524" layer="91"/>
<pinref part="GND9" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="GND10" gate="1" pin="GND"/>
<pinref part="C9" gate="C" pin="1"/>
<wire x1="154.94" y1="114.3" x2="154.94" y2="116.84" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="T2" gate="T1" pin="S"/>
<pinref part="GND11" gate="1" pin="GND"/>
<wire x1="50.8" y1="58.42" x2="50.8" y2="55.88" width="0.1524" layer="91"/>
<pinref part="R10" gate="R" pin="2"/>
<wire x1="50.8" y1="55.88" x2="50.8" y2="53.34" width="0.1524" layer="91"/>
<wire x1="48.26" y1="55.88" x2="50.8" y2="55.88" width="0.1524" layer="91"/>
<junction x="50.8" y="55.88"/>
</segment>
<segment>
<pinref part="GND12" gate="1" pin="GND"/>
<pinref part="U4" gate="U1" pin="GND"/>
<wire x1="111.76" y1="53.34" x2="111.76" y2="68.58" width="0.1524" layer="91"/>
<wire x1="111.76" y1="68.58" x2="109.22" y2="68.58" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R2" gate="R" pin="1"/>
<pinref part="GND15" gate="1" pin="GND"/>
<wire x1="83.82" y1="15.24" x2="83.82" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C6" gate="C" pin="1"/>
<pinref part="GND13" gate="1" pin="GND"/>
<wire x1="106.68" y1="17.78" x2="106.68" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND16" gate="1" pin="GND"/>
<pinref part="C3" gate="C" pin="1"/>
<wire x1="33.02" y1="12.7" x2="33.02" y2="20.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND17" gate="1" pin="GND"/>
<pinref part="U1" gate="U1" pin="GND"/>
<wire x1="48.26" y1="12.7" x2="48.26" y2="27.94" width="0.1524" layer="91"/>
<wire x1="48.26" y1="27.94" x2="50.8" y2="27.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND20" gate="1" pin="GND"/>
<wire x1="200.66" y1="33.02" x2="200.66" y2="35.56" width="0.1524" layer="91"/>
<wire x1="200.66" y1="35.56" x2="200.66" y2="38.1" width="0.1524" layer="91"/>
<wire x1="200.66" y1="38.1" x2="200.66" y2="40.64" width="0.1524" layer="91"/>
<wire x1="200.66" y1="40.64" x2="200.66" y2="50.8" width="0.1524" layer="91"/>
<wire x1="200.66" y1="50.8" x2="200.66" y2="53.34" width="0.1524" layer="91"/>
<wire x1="200.66" y1="53.34" x2="223.52" y2="53.34" width="0.1524" layer="91"/>
<pinref part="C19" gate="C" pin="1"/>
<wire x1="213.36" y1="35.56" x2="200.66" y2="35.56" width="0.1524" layer="91"/>
<junction x="200.66" y="35.56"/>
<pinref part="R15" gate="R" pin="1"/>
<wire x1="200.66" y1="40.64" x2="210.82" y2="40.64" width="0.1524" layer="91"/>
<junction x="200.66" y="40.64"/>
<pinref part="C20" gate="C" pin="1"/>
<wire x1="203.2" y1="38.1" x2="200.66" y2="38.1" width="0.1524" layer="91"/>
<junction x="200.66" y="38.1"/>
<wire x1="200.66" y1="53.34" x2="200.66" y2="58.42" width="0.1524" layer="91"/>
<junction x="200.66" y="53.34"/>
<pinref part="C15" gate="C" pin="2"/>
<wire x1="200.66" y1="58.42" x2="213.36" y2="58.42" width="0.1524" layer="91"/>
<pinref part="C16" gate="C" pin="2"/>
<wire x1="213.36" y1="50.8" x2="200.66" y2="50.8" width="0.1524" layer="91"/>
<junction x="200.66" y="50.8"/>
<pinref part="OLED1" gate="OLED1" pin="VSS"/>
</segment>
<segment>
<pinref part="GND14" gate="1" pin="GND"/>
<pinref part="D2" gate="SHOTKY" pin="A"/>
<wire x1="91.44" y1="12.7" x2="91.44" y2="15.24" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND18" gate="1" pin="GND"/>
<wire x1="198.12" y1="88.9" x2="198.12" y2="91.44" width="0.1524" layer="91"/>
<wire x1="198.12" y1="91.44" x2="198.12" y2="96.52" width="0.1524" layer="91"/>
<wire x1="198.12" y1="96.52" x2="193.04" y2="96.52" width="0.1524" layer="91"/>
<junction x="198.12" y="96.52"/>
<wire x1="198.12" y1="96.52" x2="203.2" y2="96.52" width="0.1524" layer="91"/>
<pinref part="SW1" gate="SW1" pin="2"/>
<pinref part="SW2" gate="SW1" pin="1"/>
<pinref part="SW2" gate="SW1" pin="SHIELD"/>
<wire x1="187.96" y1="91.44" x2="187.96" y2="93.98" width="0.1524" layer="91"/>
<junction x="198.12" y="96.52"/>
<pinref part="SW1" gate="SW1" pin="SHIELD"/>
<wire x1="208.28" y1="91.44" x2="208.28" y2="93.98" width="0.1524" layer="91"/>
<junction x="198.12" y="96.52"/>
<wire x1="187.96" y1="91.44" x2="198.12" y2="91.44" width="0.1524" layer="91"/>
<junction x="198.12" y="91.44"/>
<wire x1="198.12" y1="91.44" x2="208.28" y2="91.44" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND19" gate="1" pin="GND"/>
<pinref part="C8" gate="C" pin="1"/>
<wire x1="132.08" y1="12.7" x2="132.08" y2="17.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND21" gate="1" pin="GND"/>
<wire x1="226.06" y1="114.3" x2="226.06" y2="116.84" width="0.1524" layer="91"/>
<wire x1="226.06" y1="116.84" x2="236.22" y2="116.84" width="0.1524" layer="91"/>
<pinref part="SWD" gate="P" pin="1"/>
</segment>
<segment>
<pinref part="C4" gate="C" pin="1"/>
<pinref part="GND22" gate="1" pin="GND"/>
<wire x1="40.64" y1="20.32" x2="40.64" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R4" gate="R" pin="1"/>
<pinref part="GND23" gate="1" pin="GND"/>
<wire x1="147.32" y1="35.56" x2="147.32" y2="33.02" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND25" gate="1" pin="GND"/>
<pinref part="D3" gate="D" pin="A"/>
<wire x1="38.1" y1="104.14" x2="38.1" y2="106.68" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND24" gate="1" pin="GND"/>
<pinref part="D4" gate="D" pin="C"/>
<wire x1="45.72" y1="104.14" x2="45.72" y2="106.68" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C12" gate="C" pin="1"/>
<pinref part="GND26" gate="1" pin="GND"/>
<wire x1="99.06" y1="109.22" x2="99.06" y2="104.14" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C2" gate="C" pin="1"/>
<pinref part="GND28" gate="1" pin="GND"/>
<wire x1="17.78" y1="20.32" x2="17.78" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C1" gate="C" pin="1"/>
<pinref part="GND27" gate="1" pin="GND"/>
<wire x1="10.16" y1="20.32" x2="10.16" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SENSOR" class="0">
<segment>
<wire x1="106.68" y1="162.56" x2="106.68" y2="157.48" width="0.1524" layer="91"/>
<wire x1="106.68" y1="157.48" x2="137.16" y2="157.48" width="0.1524" layer="91"/>
<label x="137.16" y="157.48" size="1.778" layer="95" rot="MR0"/>
<pinref part="JACK" gate="CON" pin="3"/>
</segment>
<segment>
<wire x1="25.4" y1="124.46" x2="22.86" y2="124.46" width="0.1524" layer="91"/>
<pinref part="R6" gate="R" pin="1"/>
<label x="10.16" y="124.46" size="1.778" layer="95"/>
<pinref part="R5" gate="R" pin="1"/>
<wire x1="22.86" y1="124.46" x2="10.16" y2="124.46" width="0.1524" layer="91"/>
<wire x1="22.86" y1="127" x2="22.86" y2="124.46" width="0.1524" layer="91"/>
<junction x="22.86" y="124.46"/>
</segment>
</net>
<net name="HEATER" class="0">
<segment>
<wire x1="109.22" y1="162.56" x2="109.22" y2="160.02" width="0.1524" layer="91"/>
<wire x1="109.22" y1="160.02" x2="137.16" y2="160.02" width="0.1524" layer="91"/>
<label x="137.16" y="160.02" size="1.778" layer="95" rot="MR0"/>
<pinref part="JACK" gate="CON" pin="2"/>
</segment>
<segment>
<wire x1="76.2" y1="60.96" x2="134.62" y2="60.96" width="0.1524" layer="91"/>
<label x="134.62" y="60.96" size="1.778" layer="95" rot="MR0"/>
<wire x1="76.2" y1="60.96" x2="76.2" y2="68.58" width="0.1524" layer="91"/>
<wire x1="76.2" y1="68.58" x2="78.74" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U4" gate="U1" pin="IP-"/>
</segment>
</net>
<net name="NRST" class="0">
<segment>
<pinref part="C10" gate="C" pin="2"/>
<wire x1="162.56" y1="121.92" x2="162.56" y2="137.16" width="0.1524" layer="91"/>
<pinref part="U2" gate="U" pin="NRST"/>
<wire x1="162.56" y1="137.16" x2="172.72" y2="137.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VDDA" class="0">
<segment>
<pinref part="VDDA5" gate="VDDA" pin="VDDA"/>
<pinref part="R5" gate="R" pin="2"/>
<wire x1="22.86" y1="137.16" x2="22.86" y2="139.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U3" gate="IC" pin="V+"/>
<pinref part="C11" gate="C" pin="2"/>
<wire x1="76.2" y1="134.62" x2="76.2" y2="129.54" width="0.1524" layer="91"/>
<junction x="76.2" y="134.62"/>
<pinref part="VDDA2" gate="VDDA" pin="VDDA"/>
<wire x1="76.2" y1="134.62" x2="76.2" y2="139.7" width="0.1524" layer="91"/>
<junction x="76.2" y="134.62"/>
<pinref part="C12" gate="C" pin="2"/>
<wire x1="99.06" y1="114.3" x2="99.06" y2="134.62" width="0.1524" layer="91"/>
<wire x1="99.06" y1="134.62" x2="91.44" y2="134.62" width="0.1524" layer="91"/>
<wire x1="91.44" y1="134.62" x2="76.2" y2="134.62" width="0.1524" layer="91"/>
<wire x1="91.44" y1="114.3" x2="91.44" y2="134.62" width="0.1524" layer="91"/>
<junction x="91.44" y="134.62"/>
</segment>
<segment>
<pinref part="U4" gate="U1" pin="VCC"/>
<pinref part="VDDA4" gate="VDDA" pin="VDDA"/>
<wire x1="111.76" y1="71.12" x2="111.76" y2="83.82" width="0.1524" layer="91"/>
<wire x1="111.76" y1="71.12" x2="109.22" y2="71.12" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="VDDA1" gate="VDDA" pin="VDDA"/>
<pinref part="L2" gate="L1" pin="2"/>
<wire x1="132.08" y1="27.94" x2="129.54" y2="27.94" width="0.1524" layer="91"/>
<junction x="132.08" y="27.94"/>
<wire x1="132.08" y1="27.94" x2="132.08" y2="35.56" width="0.1524" layer="91"/>
<pinref part="C8" gate="C" pin="2"/>
<wire x1="132.08" y1="22.86" x2="132.08" y2="27.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C9" gate="C" pin="2"/>
<wire x1="154.94" y1="121.92" x2="154.94" y2="129.54" width="0.1524" layer="91"/>
<pinref part="U2" gate="U" pin="VDDA"/>
<wire x1="154.94" y1="129.54" x2="172.72" y2="129.54" width="0.1524" layer="91"/>
<junction x="154.94" y="129.54"/>
<pinref part="VDDA3" gate="VDDA" pin="VDDA"/>
<wire x1="154.94" y1="129.54" x2="154.94" y2="134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="POWER_SWITCH" class="0">
<segment>
<pinref part="T1" gate="T1" pin="G"/>
<pinref part="R12" gate="R" pin="2"/>
<pinref part="R11" gate="R" pin="2"/>
<wire x1="63.5" y1="76.2" x2="66.04" y2="76.2" width="0.1524" layer="91"/>
<wire x1="66.04" y1="76.2" x2="66.04" y2="71.12" width="0.1524" layer="91"/>
<wire x1="66.04" y1="71.12" x2="68.58" y2="71.12" width="0.1524" layer="91"/>
<wire x1="68.58" y1="71.12" x2="68.58" y2="73.66" width="0.1524" layer="91"/>
<wire x1="66.04" y1="71.12" x2="63.5" y2="71.12" width="0.1524" layer="91"/>
<junction x="66.04" y="71.12"/>
</segment>
</net>
<net name="HEATER_CONTROL" class="0">
<segment>
<pinref part="T2" gate="T1" pin="G"/>
<wire x1="45.72" y1="60.96" x2="35.56" y2="60.96" width="0.1524" layer="91"/>
<label x="10.16" y="60.96" size="1.778" layer="95"/>
<pinref part="R10" gate="R" pin="1"/>
<wire x1="35.56" y1="60.96" x2="10.16" y2="60.96" width="0.1524" layer="91"/>
<wire x1="38.1" y1="55.88" x2="35.56" y2="55.88" width="0.1524" layer="91"/>
<wire x1="35.56" y1="55.88" x2="35.56" y2="60.96" width="0.1524" layer="91"/>
<junction x="35.56" y="60.96"/>
</segment>
<segment>
<label x="147.32" y="160.02" size="1.778" layer="95"/>
<pinref part="U2" gate="U" pin="PB3/SCK"/>
<wire x1="147.32" y1="160.02" x2="172.72" y2="160.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="HEATER_PWR" class="0">
<segment>
<pinref part="T1" gate="T1" pin="D"/>
<wire x1="78.74" y1="78.74" x2="76.2" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U4" gate="U1" pin="IP+"/>
</segment>
</net>
<net name="CURRENT_SENS" class="0">
<segment>
<pinref part="U4" gate="U1" pin="VIOUT"/>
<wire x1="109.22" y1="78.74" x2="134.62" y2="78.74" width="0.1524" layer="91"/>
<label x="134.62" y="78.74" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="223.52" y1="162.56" x2="246.38" y2="162.56" width="0.1524" layer="91"/>
<label x="246.38" y="162.56" size="1.778" layer="95" rot="MR0"/>
<pinref part="U2" gate="U" pin="T2C1/PA0"/>
</segment>
</net>
<net name="SUPPLY_CB" class="0">
<segment>
<pinref part="U1" gate="U1" pin="CB"/>
<pinref part="C5" gate="C" pin="1"/>
<wire x1="81.28" y1="33.02" x2="83.82" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SWOUT" class="0">
<segment>
<pinref part="U1" gate="U1" pin="SW"/>
<wire x1="81.28" y1="30.48" x2="91.44" y2="30.48" width="0.1524" layer="91"/>
<wire x1="91.44" y1="30.48" x2="91.44" y2="33.02" width="0.1524" layer="91"/>
<pinref part="C5" gate="C" pin="2"/>
<wire x1="91.44" y1="33.02" x2="88.9" y2="33.02" width="0.1524" layer="91"/>
<pinref part="L1" gate="L1" pin="1"/>
<wire x1="91.44" y1="33.02" x2="93.98" y2="33.02" width="0.1524" layer="91"/>
<junction x="91.44" y="33.02"/>
<pinref part="D2" gate="SHOTKY" pin="C"/>
<wire x1="91.44" y1="25.4" x2="91.44" y2="30.48" width="0.1524" layer="91"/>
<junction x="91.44" y="30.48"/>
</segment>
</net>
<net name="SUPPLY_FB" class="0">
<segment>
<pinref part="U1" gate="U1" pin="FB"/>
<pinref part="R1" gate="R" pin="1"/>
<wire x1="81.28" y1="27.94" x2="83.82" y2="27.94" width="0.1524" layer="91"/>
<pinref part="R2" gate="R" pin="2"/>
<wire x1="83.82" y1="27.94" x2="93.98" y2="27.94" width="0.1524" layer="91"/>
<wire x1="83.82" y1="25.4" x2="83.82" y2="27.94" width="0.1524" layer="91"/>
<junction x="83.82" y="27.94"/>
</segment>
</net>
<net name="C2P" class="0">
<segment>
<pinref part="C18" gate="C" pin="1"/>
<pinref part="OLED1" gate="OLED1" pin="C2P"/>
<wire x1="218.44" y1="68.58" x2="223.52" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="C1P" class="0">
<segment>
<pinref part="C17" gate="C" pin="1"/>
<pinref part="OLED1" gate="OLED1" pin="C1P"/>
<wire x1="218.44" y1="63.5" x2="223.52" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="C1N" class="0">
<segment>
<wire x1="210.82" y1="60.96" x2="210.82" y2="63.5" width="0.1524" layer="91"/>
<pinref part="C17" gate="C" pin="2"/>
<wire x1="210.82" y1="63.5" x2="213.36" y2="63.5" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="C1N"/>
<wire x1="210.82" y1="60.96" x2="223.52" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="C2N" class="0">
<segment>
<pinref part="C18" gate="C" pin="2"/>
<wire x1="213.36" y1="68.58" x2="210.82" y2="68.58" width="0.1524" layer="91"/>
<wire x1="210.82" y1="68.58" x2="210.82" y2="66.04" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="C2N"/>
<wire x1="210.82" y1="66.04" x2="223.52" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="C19" gate="C" pin="2"/>
<wire x1="218.44" y1="35.56" x2="223.52" y2="35.56" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="VCC"/>
</segment>
</net>
<net name="VCOM" class="0">
<segment>
<pinref part="C20" gate="C" pin="2"/>
<pinref part="OLED1" gate="OLED1" pin="VCOM"/>
<wire x1="208.28" y1="38.1" x2="223.52" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="IREF" class="0">
<segment>
<pinref part="R15" gate="R" pin="2"/>
<wire x1="220.98" y1="40.64" x2="223.52" y2="40.64" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="IREF"/>
</segment>
</net>
<net name="OLED_NRES" class="0">
<segment>
<label x="177.8" y="48.26" size="1.778" layer="95"/>
<pinref part="OLED1" gate="OLED1" pin="NRES"/>
<wire x1="177.8" y1="48.26" x2="223.52" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="246.38" y="129.54" size="1.778" layer="95" rot="MR0"/>
<pinref part="U2" gate="U" pin="PA15"/>
<wire x1="223.52" y1="129.54" x2="246.38" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="BTN1" class="0">
<segment>
<label x="226.06" y="96.52" size="1.778" layer="95" rot="MR0"/>
<pinref part="SW1" gate="SW1" pin="1"/>
<wire x1="213.36" y1="96.52" x2="226.06" y2="96.52" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="172.72" y1="157.48" x2="147.32" y2="157.48" width="0.1524" layer="91"/>
<label x="147.32" y="157.48" size="1.778" layer="95"/>
<pinref part="U2" gate="U" pin="PB4/MISO"/>
</segment>
</net>
<net name="BTN2" class="0">
<segment>
<label x="170.18" y="96.52" size="1.778" layer="95"/>
<pinref part="SW2" gate="SW1" pin="2"/>
<wire x1="182.88" y1="96.52" x2="170.18" y2="96.52" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="172.72" y1="154.94" x2="147.32" y2="154.94" width="0.1524" layer="91"/>
<label x="147.32" y="154.94" size="1.778" layer="95"/>
<pinref part="U2" gate="U" pin="PB5/MOSI"/>
</segment>
</net>
<net name="SCL" class="0">
<segment>
<pinref part="R14" gate="R" pin="1"/>
<wire x1="198.12" y1="58.42" x2="198.12" y2="45.72" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="SCL"/>
<wire x1="223.52" y1="45.72" x2="198.12" y2="45.72" width="0.1524" layer="91"/>
<label x="177.8" y="45.72" size="1.778" layer="95"/>
<wire x1="198.12" y1="45.72" x2="177.8" y2="45.72" width="0.1524" layer="91"/>
<junction x="198.12" y="45.72"/>
</segment>
<segment>
<pinref part="U2" gate="U" pin="SCL/TX/T1C2/PA9"/>
<wire x1="223.52" y1="139.7" x2="246.38" y2="139.7" width="0.1524" layer="91"/>
<label x="246.38" y="139.7" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
<net name="SDA" class="0">
<segment>
<pinref part="R13" gate="R" pin="1"/>
<wire x1="193.04" y1="53.34" x2="193.04" y2="43.18" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="SDA"/>
<wire x1="223.52" y1="43.18" x2="193.04" y2="43.18" width="0.1524" layer="91"/>
<label x="177.8" y="43.18" size="1.778" layer="95"/>
<wire x1="193.04" y1="43.18" x2="177.8" y2="43.18" width="0.1524" layer="91"/>
<junction x="193.04" y="43.18"/>
</segment>
<segment>
<pinref part="U2" gate="U" pin="SDA/RX/T1C3/PA10"/>
<wire x1="223.52" y1="137.16" x2="246.38" y2="137.16" width="0.1524" layer="91"/>
<label x="246.38" y="137.16" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
<net name="SWDIO" class="0">
<segment>
<wire x1="236.22" y1="121.92" x2="228.6" y2="121.92" width="0.1524" layer="91"/>
<wire x1="228.6" y1="121.92" x2="228.6" y2="134.62" width="0.1524" layer="91"/>
<pinref part="U2" gate="U" pin="SWDIO/PA13"/>
<wire x1="228.6" y1="134.62" x2="223.52" y2="134.62" width="0.1524" layer="91"/>
<pinref part="SWD" gate="P" pin="3"/>
</segment>
</net>
<net name="SWDCLK" class="0">
<segment>
<pinref part="U2" gate="U" pin="SWCLK/PA14"/>
<wire x1="223.52" y1="132.08" x2="226.06" y2="132.08" width="0.1524" layer="91"/>
<wire x1="226.06" y1="132.08" x2="226.06" y2="119.38" width="0.1524" layer="91"/>
<wire x1="226.06" y1="119.38" x2="236.22" y2="119.38" width="0.1524" layer="91"/>
<pinref part="SWD" gate="P" pin="2"/>
</segment>
</net>
<net name="DEBUG_OUT" class="0">
<segment>
<pinref part="U2" gate="U" pin="T2C3/TX/PA2"/>
<wire x1="223.52" y1="157.48" x2="246.38" y2="157.48" width="0.1524" layer="91"/>
<pinref part="TP1" gate="TP" pin="TP"/>
</segment>
</net>
<net name="12V_DC" class="0">
<segment>
<pinref part="C3" gate="C" pin="2"/>
<pinref part="U1" gate="U1" pin="VIN"/>
<wire x1="33.02" y1="25.4" x2="33.02" y2="30.48" width="0.1524" layer="91"/>
<wire x1="33.02" y1="30.48" x2="40.64" y2="30.48" width="0.1524" layer="91"/>
<wire x1="40.64" y1="30.48" x2="40.64" y2="33.02" width="0.1524" layer="91"/>
<wire x1="40.64" y1="33.02" x2="50.8" y2="33.02" width="0.1524" layer="91"/>
<pinref part="U1" gate="U1" pin="SHDN"/>
<wire x1="50.8" y1="30.48" x2="40.64" y2="30.48" width="0.1524" layer="91"/>
<junction x="40.64" y="30.48"/>
<pinref part="D1" gate="SHOTKY" pin="C"/>
<pinref part="C4" gate="C" pin="2"/>
<wire x1="40.64" y1="30.48" x2="40.64" y2="25.4" width="0.1524" layer="91"/>
<wire x1="33.02" y1="30.48" x2="30.48" y2="30.48" width="0.1524" layer="91"/>
<junction x="33.02" y="30.48"/>
</segment>
</net>
<net name="POWER_SWITCH_LOW" class="0">
<segment>
<pinref part="T2" gate="T1" pin="D"/>
<pinref part="R11" gate="R" pin="1"/>
<wire x1="53.34" y1="71.12" x2="50.8" y2="71.12" width="0.1524" layer="91"/>
<wire x1="50.8" y1="71.12" x2="50.8" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="3V3" class="0">
<segment>
<pinref part="C6" gate="C" pin="2"/>
<pinref part="R1" gate="R" pin="2"/>
<wire x1="104.14" y1="27.94" x2="106.68" y2="27.94" width="0.1524" layer="91"/>
<pinref part="L1" gate="L1" pin="2"/>
<wire x1="104.14" y1="33.02" x2="106.68" y2="33.02" width="0.1524" layer="91"/>
<pinref part="3V2" gate="3V3" pin="3V3"/>
<junction x="106.68" y="33.02"/>
<wire x1="106.68" y1="33.02" x2="106.68" y2="27.94" width="0.1524" layer="91"/>
<junction x="106.68" y="27.94"/>
<wire x1="106.68" y1="27.94" x2="106.68" y2="22.86" width="0.1524" layer="91"/>
<pinref part="L2" gate="L1" pin="1"/>
<wire x1="119.38" y1="27.94" x2="116.84" y2="27.94" width="0.1524" layer="91"/>
<pinref part="C7" gate="C" pin="2"/>
<wire x1="116.84" y1="22.86" x2="116.84" y2="27.94" width="0.1524" layer="91"/>
<junction x="116.84" y="27.94"/>
<wire x1="106.68" y1="27.94" x2="116.84" y2="27.94" width="0.1524" layer="91"/>
<wire x1="106.68" y1="33.02" x2="116.84" y2="33.02" width="0.1524" layer="91"/>
<wire x1="116.84" y1="33.02" x2="116.84" y2="27.94" width="0.1524" layer="91"/>
<wire x1="116.84" y1="35.56" x2="116.84" y2="33.02" width="0.1524" layer="91"/>
<junction x="116.84" y="33.02"/>
</segment>
<segment>
<pinref part="U2" gate="U" pin="VDD"/>
<wire x1="172.72" y1="127" x2="147.32" y2="127" width="0.1524" layer="91"/>
<pinref part="3V3" gate="3V3" pin="3V3"/>
<wire x1="147.32" y1="134.62" x2="147.32" y2="127" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C15" gate="C" pin="1"/>
<wire x1="218.44" y1="58.42" x2="220.98" y2="58.42" width="0.1524" layer="91"/>
<pinref part="C16" gate="C" pin="1"/>
<wire x1="220.98" y1="50.8" x2="218.44" y2="50.8" width="0.1524" layer="91"/>
<wire x1="220.98" y1="50.8" x2="220.98" y2="58.42" width="0.1524" layer="91"/>
<junction x="220.98" y="50.8"/>
<junction x="220.98" y="58.42"/>
<wire x1="220.98" y1="58.42" x2="220.98" y2="71.12" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="VBAT"/>
<wire x1="220.98" y1="58.42" x2="223.52" y2="58.42" width="0.1524" layer="91"/>
<pinref part="OLED1" gate="OLED1" pin="VDD"/>
<wire x1="220.98" y1="50.8" x2="223.52" y2="50.8" width="0.1524" layer="91"/>
<pinref part="3V1" gate="3V3" pin="3V3"/>
</segment>
<segment>
<pinref part="R13" gate="R" pin="2"/>
<wire x1="193.04" y1="63.5" x2="193.04" y2="71.12" width="0.1524" layer="91"/>
<pinref part="3V4" gate="3V3" pin="3V3"/>
</segment>
<segment>
<pinref part="R14" gate="R" pin="2"/>
<wire x1="198.12" y1="71.12" x2="198.12" y2="68.58" width="0.1524" layer="91"/>
<pinref part="3V5" gate="3V3" pin="3V3"/>
</segment>
</net>
<net name="12V" class="0">
<segment>
<pinref part="D1" gate="SHOTKY" pin="A"/>
<pinref part="C1" gate="C" pin="2"/>
<pinref part="12V1" gate="12V" pin="12V"/>
<pinref part="C2" gate="C" pin="2"/>
<wire x1="17.78" y1="30.48" x2="17.78" y2="25.4" width="0.1524" layer="91"/>
<wire x1="17.78" y1="30.48" x2="10.16" y2="30.48" width="0.1524" layer="91"/>
<wire x1="10.16" y1="30.48" x2="10.16" y2="35.56" width="0.1524" layer="91"/>
<wire x1="10.16" y1="30.48" x2="10.16" y2="25.4" width="0.1524" layer="91"/>
<junction x="10.16" y="30.48"/>
<wire x1="20.32" y1="30.48" x2="17.78" y2="30.48" width="0.1524" layer="91"/>
<junction x="17.78" y="30.48"/>
</segment>
<segment>
<pinref part="R12" gate="R" pin="1"/>
<wire x1="53.34" y1="76.2" x2="50.8" y2="76.2" width="0.1524" layer="91"/>
<pinref part="12V4" gate="12V" pin="12V"/>
<wire x1="50.8" y1="83.82" x2="50.8" y2="76.2" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R3" gate="R" pin="2"/>
<wire x1="147.32" y1="63.5" x2="147.32" y2="60.96" width="0.1524" layer="91"/>
<pinref part="12V3" gate="12V" pin="12V"/>
</segment>
<segment>
<pinref part="T1" gate="T1" pin="S"/>
<wire x1="66.04" y1="78.74" x2="63.5" y2="78.74" width="0.1524" layer="91"/>
<wire x1="63.5" y1="78.74" x2="63.5" y2="83.82" width="0.1524" layer="91"/>
<pinref part="12V2" gate="12V" pin="12V"/>
</segment>
</net>
<net name="TEMP_SENS" class="0">
<segment>
<wire x1="223.52" y1="160.02" x2="246.38" y2="160.02" width="0.1524" layer="91"/>
<label x="246.38" y="160.02" size="1.778" layer="95" rot="MR0"/>
<pinref part="U2" gate="U" pin="T2C2/PA1"/>
</segment>
<segment>
<wire x1="111.76" y1="121.92" x2="114.3" y2="121.92" width="0.1524" layer="91"/>
<wire x1="114.3" y1="121.92" x2="114.3" y2="114.3" width="0.1524" layer="91"/>
<wire x1="114.3" y1="121.92" x2="134.62" y2="121.92" width="0.1524" layer="91"/>
<junction x="114.3" y="121.92"/>
<pinref part="R9" gate="R" pin="2"/>
<pinref part="C14" gate="C" pin="2"/>
<label x="134.62" y="121.92" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
<net name="SUPPLY_SENS" class="0">
<segment>
<wire x1="223.52" y1="154.94" x2="246.38" y2="154.94" width="0.1524" layer="91"/>
<label x="246.38" y="154.94" size="1.778" layer="95" rot="MR0"/>
<pinref part="U2" gate="U" pin="T2C4/RX/PA3"/>
</segment>
<segment>
<pinref part="R3" gate="R" pin="1"/>
<pinref part="R4" gate="R" pin="2"/>
<wire x1="147.32" y1="50.8" x2="147.32" y2="48.26" width="0.1524" layer="91"/>
<wire x1="147.32" y1="48.26" x2="147.32" y2="45.72" width="0.1524" layer="91"/>
<wire x1="147.32" y1="48.26" x2="170.18" y2="48.26" width="0.1524" layer="91"/>
<junction x="147.32" y="48.26"/>
<label x="170.18" y="48.26" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
