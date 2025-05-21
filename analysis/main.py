from analysis import HadronShowerAnalysis


###################################
# setting directory and filenames #
###################################
data_directory = "/Users/brynlloyd/Developer/Coding/geant4/FBIV/hadron_shower/data/"
# look at what happens to the hadron shower energy spectra when you change the amount of uranium in the sample
filenames = ["KE_data_feni.csv", "KE_data_feni10u.csv", "KE_data_feni01u.csv"]

# same as above but for plutonium
# filenames = ["KE_data_feni.csv", "KE_data_feni10pu.csv", "KE_data_feni01pu.csv"]

# same as above but for californium
# filenames = ["KE_data_feni.csv", "KE_data_feni10ca.csv", "KE_data_feni01ca.csv"]

# comparing whether different high-z inclusions leave different imprints on the hadron shower
# filenames = ["KE_data_feni.csv", "KE_data_feni01u.csv", "KE_data_feni01pu.csv", "KE_data_feni01ca.csv"]


####################
# running analysis #
####################


# instantiate the analysis class
analysis = HadronShowerAnalysis(data_directory, filenames)


# these are the three main methods for the class

# prints out a table of the number of counts of the different particle species
analysis.compare_particle_numbers()

# plots a single histogram
# main use is to make sure that the energy cutoffs are appropriate since they are just hardcoded in
# analysis.plot_single(filenames[0], "gamma")

# plots energy spectra for all of the most common particle types
analysis.plot_comparison()
