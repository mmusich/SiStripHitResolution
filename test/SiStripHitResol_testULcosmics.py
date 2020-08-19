import FWCore.ParameterSet.Config as cms

process = cms.Process("HitEff")
process.load("Configuration/StandardSequences/MagneticField_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')  

process.source = cms.Source("PoolSource", fileNames=cms.untracked.vstring(
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/C88E7B45-E0DA-0742-B622-25C2C9E0AC58.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/08894276-BD9E-454E-96A9-8E30BE93C0C7.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/FEA63E84-13F5-3246-BF7D-D7F4C257D419.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/09A05CD3-7D70-B141-870D-DE3BA2E58D96.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/47887C90-18C4-4B4D-86A3-70E6004E2076.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/B481DEBC-037D-1D4D-A767-38FE8A49F8E6.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/D53E4B8C-5D15-D14E-9ABA-047E21DF1A8C.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/330C361E-0D9E-2C46-9805-F292DCF3C3F9.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/510000/B2586374-7ED0-3C4A-9B2C-7A2991A32CDB.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/90CFCA29-7CB7-A145-9E37-779FEA9EDBBB.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/0C458F23-0922-164C-B1A6-306F77DDA853.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/8A5EC816-5F22-BA4F-B01C-36E33A1709DC.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/6737DF42-C8FE-2D42-934D-3C136DCF67A0.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/B803C62D-D3BE-AF42-86A5-239A23A27E46.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/1E91E801-2873-EE45-84FE-DBB752D30B3D.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/2E1015D3-911A-A749-B3B6-88722A7E28E3.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/6B69D370-A739-9D4C-AB04-7D3797214F7A.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/DB1B1C5E-6A8C-364A-814E-10CF7C6F0555.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/FC461B90-05AF-0D47-8381-75E5F8FE1BE6.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/98C6B766-5175-F944-9715-619949A53697.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/33B21065-5027-4442-804F-6C0A18500590.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/F6662AB1-DD84-DA4E-A0C9-F6F2F639821F.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/69ED8F1F-DFE7-EC44-B01A-3B98A03375F9.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/230000/477A0F21-EE03-0646-B94E-A69FE6854E6D.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/EB4BBA67-5816-954F-ADB9-88C9A98B5C28.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/10B71E29-B201-B248-AC9E-6FF3352488AC.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/974701BE-1BE9-8442-8DF4-3AC8C90DEEEB.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/CC0E661D-3AE2-4B49-85CE-2069A1E5FDFF.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/DC711AEB-F292-F344-91CF-718A8D0DEDF2.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/33CC1571-409F-404C-9AAC-DDCEFB21E963.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/421DD12A-ACE6-7641-A616-59DC3F36785A.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/EB34EA65-2772-CB42-857E-BD894F0DDBDB.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/AFF38795-5C87-9B4A-B755-99BAD0C416BB.root",
    "file:/eos/cms/store/data/Run2018C/Cosmics/ALCARECO/SiStripCalCosmics-UL18-v1/40000/68F16890-CF8F-284A-8818-EF0E0E786EFE.root"
    ))

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

process.load("RecoVertex.BeamSpotProducer.BeamSpot_cfi")

#process.load("RecoLocalTracker.SiStripRecHitConverter.StripCPEfromTrackAngle_cfi")
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")

process.refitTracks = process.TrackRefitterP5.clone(src=cms.InputTag("ALCARECOSiStripCalCosmics"))

process.load("UserCode.SiStripHitResolution.SiStripHitResol_cff")
process.anResol.combinatorialTracks = cms.InputTag("refitTracks")
process.anResol.trajectories = cms.InputTag("refitTracks")

process.TFileService = cms.Service("TFileService",
        fileName = cms.string("hitresol.root")  
)

process.allPath = cms.Path(process.MeasurementTrackerEvent*process.offlineBeamSpot*process.refitTracks*process.hitresol)
