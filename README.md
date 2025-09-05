CSPICE DLL
===========

For usage in C#. Use the CSPICE.cs class to expose the DLL Functions.

1. furnsh_c(string file)
------------------------

Loads SPICE kernel files into the internal data pool.

example:
    CSPICE.furnsh_c("de430.bsp");
    CSPICE.furnsh_c("naif0012.tls");
(loads spice kernels)


2. str2et_c(string time, out double et)
---------------------------------------

Converts UTC time string to ET (ephemeris time)

example:
    string utc = timestamp.ToUniversalTime().ToString("yyyy MMM dd HH:mm:ss");
    CSPICE.str2et_c(utc, out double et);


3. spkezr_c(...)
----------------

Retrieves the state vector (position and velocity) of a target body relative to an observer at a specific time.

Parameters:
target: Name or ID of the target body (e.g., "MARS").
et: Ephemeris time (obtained from str2et_c).
refFrame: Reference frame (e.g., "J2000").
abcorr: Aberration correction flag (e.g., "NONE", "LT", "LT+S").
observer: Name or ID of the observing body (e.g., "EARTH").
state: Output array [x, y, z, vx, vy, vz] giving the target’s position (km) and velocity (km/s).
lightTime: Output scalar, time light takes to travel from target to observer (seconds).


4. reclat_c(double[] rectan, out double radius, out double lon, out double lat)
--------------------------------------------------------------------------------

Converts rectangular (Cartesian) coordinates to latitudinal coordinates.

rectan: Input rectangular coordinates [x, y, z] (km).
radius: Output radial distance (km).
lon: Output longitude (radians).
lat: Output latitude (radians).


example use of spkezr_c and reclat_c:
-------------------------------------

    // --- Load Planets ---
    string[] planetNames = {
        "MERCURY BARYCENTER", "VENUS BARYCENTER", "EARTH BARYCENTER",
        "MARS BARYCENTER", "JUPITER BARYCENTER", "SATURN BARYCENTER",
        "URANUS BARYCENTER", "NEPTUNE BARYCENTER"
    };
    string[] commonNames = {
        "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"
    };

    for (int i = 0; i < planetNames.Length; i++)
    {
        double[] state = new double[6];
        CSPICE.spkezr_c(planetNames[i], et, "J2000", "LT+S", "EARTH", state, out double lt);
        CSPICE.reclat_c(state, out double radius, out double lon, out double lat);

        Planets.Add(new Planet(
            commonNames[i],
            lon * (180.0 / Math.PI),
            lat * (180.0 / Math.PI),
            radius / 149597870.7
        ));
    }

    // --- Load Sun ---
    double[] sunState = new double[6];
    CSPICE.spkezr_c("SUN", et, "J2000", "LT+S", "EARTH", sunState, out double sunLt);
    CSPICE.reclat_c(sunState, out double rSun, out double lonSun, out double latSun);
    Sun = new Sun
    {
        RA = lonSun * (180.0 / Math.PI),
        Dec = latSun * (180.0 / Math.PI)
    };
