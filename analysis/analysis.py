import matplotlib.pyplot as plt
import pandas as pd

from string_utils import extract_percentage_and_element


class HadronShowerAnalysis:
    """
    Collection of methods for analysis of geant4 hadron shower data

    Attributes:
    data_dir (string): path to directory containing data
    filenames (list[string]): list of filenames from data_dir directory that should be used in the analysis
    data (dict): dictionary of the format filename: pd.DataFrame
    cutoff_energies: dictionary of the format particle: int, that stored the energy cutoff used in the analysis for each type of particle
    """

    def __init__(self, data_directory, filenames):
        """
        Initialises the class with the provided parameters

        Parameters:
        data_directory (string): path to data file
        filenames (list[string]): list of filenames to load data from
        """

        # loading data into a dictionary of dataframes
        # self.data_dir = "/Users/brynlloyd/Developer/Coding/geant4/FBIV/data/"
        self.data_dir = data_directory
        self.filenames = filenames
        self.data = {}
        for filename in self.filenames:
            key = self.get_key(filename)
            dataframe = self.load_data(filename)
            self.data[key] = dataframe

        # only considering these particles as there is ~ order of magnitude drop in the number of particles to the next most common particle
        self.cutoff_energies = {"gamma": 5,
                                "e-": 50,
                                "e+": 50,
                                "neutron": 25,
                                "pi-": 5000,
                                "pi+": 5000,
                                "proton": 1000}

    def load_data(self, filename):
        """
        returns dataframe from csv

        Parameters:
        filename (string): filename from which to load data

        Returns:
        pd.DataFrame: data from the file
        """

        dataframe = pd.read_csv(f"{self.data_dir}{filename}")
        return dataframe

    def get_key(self, filename):
        """
        takes a filename and returns a shortened string that is used to identify the data

        Paramters:
        filename (string): filename

        Returns:
        string: used as an identifier for the data in the file
        """
        prefix_len = 8  # prefix = "KE_data_"
        suffix_len = 4  # suffix = ".csv"
        return filename[prefix_len: -suffix_len]

    def compare_particle_numbers(self):
        """
        prints out dataframe of the number of occurences of each particle from each file
        """

        counts = {}
        for key, data in self.data.items():
            counts[key] = data["particleName"].value_counts()
        counts_df = pd.DataFrame(counts).fillna(0).astype(int)
        print(counts_df.sort_values(by=next(iter(self.data)), ascending=False))

    def get_particle_df(self, df, particle):
        """
        filters dataframe to give just data for a given particle

        Paramters:
        df (pd.DataFrame): dataframe of hadron shower data
        particle (string): particle name

        Returns:
        pd.DataFrame
        """
        return df[df["particleName"] == particle]

    def filter_particle_df(self, particle_df, cutoff_energy):
        """
        filters dataframe containing only a single particle type
        only want data below some cutoff energy to simplify analysis

        Parameters:
        particle_df (pd.Dataframe): dataframe from a single file, filtered to contain data for a single particle
        cutoff_energy (int): cutoff energy

        Returns:
        pd.DataFrame
        """
        return particle_df[particle_df["kineticEnergy[MeV]"] < cutoff_energy]

    def plot_filtered_particle_histogram(self, df, particle, axis):
        """
        plots the energy spectrum of a particle on a matplotlib axis

        Parameters:
        df (pd.DataFrame): unfiltered dataframe, comes directly from a data file
        particle (string): particle name
        axis (matplotlib ax instance): axis on which to plot the histogram
        """
        particle_df = self.get_particle_df(df, particle)

        if particle in self.cutoff_energies:
            cutoff_energy = self.cutoff_energies[particle]
        else:
            cutoff_energy = max(particle_df["kineticEnergy[MeV]"])

        filtered_particle_df = self.filter_particle_df(
            particle_df, cutoff_energy)
        axis.hist(
            filtered_particle_df["kineticEnergy[MeV]"], bins=500, histtype="step")

    def plot_single(self, filename, particle):
        """
        creates single axis, and calls plot_filtered_particle_histogram()

        Paramters:
        filename (string): filename
        particle (string): particle name
        """
        key = self.get_key(filename)
        df = self.data[key]

        fig, ax = plt.subplots(figsize=(10, 6))
        ax.set_title(f"Energy distribution for {particle}")
        ax.set_xlabel("Energy [MeV]")
        ax.set_ylabel("Counts")

        self.plot_filtered_particle_histogram(df, particle, ax)
        plt.show()

    def plot_comparison(self):
        """
        plot histograms for each file, but only for the particles with cutoff energies defined
        - because these are the particle species with enough counts for there to be a useful comparison
        """

        nrows, ncols = (2, 4)
        fig, axs = plt.subplots(nrows, ncols, figsize=(3 * ncols, 3 * nrows))
        for i, ax in enumerate(axs.flatten()):

            # there are 8 subplots, but only 7 particle types worth plotting...
            try:
                ax.set_title(
                    f"Energy distribution of {list(self.cutoff_energies.keys())[i]}")
            except:
                ax.axis("off")

            ax.set_xlabel("Energy [MeV]")
            ax.set_ylabel("Counts")

        # for each data file
        for key, df in self.data.items():
            # for each particle that has a defined cutoff energy
            for i, particle in enumerate(self.cutoff_energies.keys()):
                particle_df = self.get_particle_df(df, particle)
                cutoff_energy = self.cutoff_energies[particle]
                filtered_particle_df = self.filter_particle_df(
                    particle_df, cutoff_energy)

                # for each histogram, calculate the Hellinger distance to the undoped meteorite case
                # to be used as a label in the legend in the plot
                undoped_name = "feni"
                if key != undoped_name:
                    percentage, element = extract_percentage_and_element(key)
                    label = f"{percentage}% {element}"
                else:
                    label = "undoped case"

                ax = axs.flatten()[i]
                ax.hist(filtered_particle_df["kineticEnergy[MeV]"],
                        bins=500, histtype="step", label=label)
                ax.legend()
        plt.show()
