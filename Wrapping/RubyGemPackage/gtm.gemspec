Gem::Specification.new do |s|
  s.name               = "gtm"
  s.version            = "0.0.1"
  s.default_executable = "gtm"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Luis Ibanez"]
  s.date = %q{2013-03-02}
  s.description = %q{Driver for the GT.M database}
  s.email = %q{luis.ibanez@kitware.com}
  s.files = ["Rakefile", "lib/gtm.so"]
  s.test_files = ["test/gtm001.rb","test/gtm002.rb","test/gtm003.rb","test/gtm004.rb","test/gtm005.rb","test/gtm006.rb",]
  s.homepage = %q{https://github.com/OSEHRA-Sandbox/gtm-bindings}
  s.require_paths = ["lib"]
  s.rubygems_version = %q{1.6.2}
  s.summary = %q{GT.M Database!}

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
    else
    end
  else
  end
end

